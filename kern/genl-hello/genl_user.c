#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#include <linux/genetlink.h>


//宏定义：根据generic netlink msg的具体构造定位
#define GENLMSG_DATA(glh) ((void *)(NLMSG_DATA(glh) + GENL_HDRLEN))
#define GENLMSG_PAYLOAD(glh) (NLMSG_PAYLOAD(glh, 0) - GENL_HDRLEN)
#define NLA_DATA(na) ((void *)((char*)(na) + NLA_HDRLEN))

#define MESSAGE_TO_KERNEL "Hello World from user space!"

int nl_fd;  
struct sockaddr_nl nl_address; 
int nl_family_id; 
int len;
struct nlattr *nl_na;  
struct { //
    struct nlmsghdr n;
    struct genlmsghdr g;
    char buf[256];
} nl_request_msg, nl_response_msg;


int main(void) {
	nl_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	if (nl_fd < 0) {
		perror("socket()");
		return -1;
	}

	memset(&nl_address, 0, sizeof(nl_address));
	nl_address.nl_family = AF_NETLINK;
	nl_address.nl_groups = 0;

	if (bind(nl_fd, (struct sockaddr *) &nl_address, sizeof(nl_address)) < 0) {
		perror("bind()");
		close(nl_fd);
		return -1;
	}

	nl_request_msg.n.nlmsg_type = GENL_ID_CTRL;//这是内核中genl_ctl的id
	nl_request_msg.n.nlmsg_flags = NLM_F_REQUEST;
	nl_request_msg.n.nlmsg_seq = 0;
	nl_request_msg.n.nlmsg_pid = getpid();
	nl_request_msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
    	//Populate the payload's "family header" : which in our case is genlmsghdr
	nl_request_msg.g.cmd = CTRL_CMD_GETFAMILY;
	nl_request_msg.g.version = 0x1;
    	//Populate the payload's "netlink attributes"
	nl_na = (struct nlattr *) GENLMSG_DATA(&nl_request_msg);//其实就相当于在nl_request_msg 的buf域中构造一个nla

	nl_na->nla_type = CTRL_ATTR_FAMILY_NAME;
	nl_na->nla_len = strlen("CONTROL_EXMPL") + 1 + NLA_HDRLEN;
	strcpy(NLA_DATA(nl_na), "CONTROL_EXMPL"); //Family name length can be upto 16 chars including \0
    
	nl_request_msg.n.nlmsg_len += NLMSG_ALIGN(nl_na->nla_len);

	memset(&nl_address, 0, sizeof(nl_address));
	nl_address.nl_family = AF_NETLINK;

	len= sendto(nl_fd, (char *) &nl_request_msg, nl_request_msg.n.nlmsg_len,
		       0, (struct sockaddr *) &nl_address, sizeof(nl_address));
	if (len != nl_request_msg.n.nlmsg_len) {
		perror("sendto()");
		close(nl_fd);
		return -1;
	}

	len= recv(nl_fd, &nl_response_msg, sizeof(nl_response_msg), 0);
	if (len < 0) {
	        perror("recv()");
	        return -1;
	}

	if (!NLMSG_OK((&nl_response_msg.n), len)) {
        	fprintf(stderr, "family ID request : invalid message\n");
        	return -1;
	}
	if (nl_response_msg.n.nlmsg_type == NLMSG_ERROR) { //error
        	fprintf(stderr, "family ID request : receive error\n");
        	return -1;
    	}

    	//解析出attribute中的family id
    	nl_na = (struct nlattr *) GENLMSG_DATA(&nl_response_msg);
    	nl_na = (struct nlattr *) ((char *) nl_na + NLA_ALIGN(nl_na->nla_len));
    	if (nl_na->nla_type == CTRL_ATTR_FAMILY_ID) {
        	nl_family_id = *(__u16 *) NLA_DATA(nl_na);//第一次通信就是为了得到需要的family ID
    	}

	memset(&nl_request_msg, 0, sizeof(nl_request_msg));
	memset(&nl_response_msg, 0, sizeof(nl_response_msg));

    	nl_request_msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
    	nl_request_msg.n.nlmsg_type = nl_family_id;
    	nl_request_msg.n.nlmsg_flags = NLM_F_REQUEST;
    	nl_request_msg.n.nlmsg_seq = 60;
    	nl_request_msg.n.nlmsg_pid = getpid();
    	nl_request_msg.g.cmd = 1; //corresponds to DOC_EXMPL_C_ECHO;
        
	nl_na = (struct nlattr *) GENLMSG_DATA(&nl_request_msg);
    	nl_na->nla_type = 1; // corresponds to DOC_EXMPL_A_MSG
    	nl_na->nla_len = sizeof(MESSAGE_TO_KERNEL)+NLA_HDRLEN; //Message length
    	memcpy(NLA_DATA(nl_na), MESSAGE_TO_KERNEL, sizeof(MESSAGE_TO_KERNEL));
    	nl_request_msg.n.nlmsg_len += NLMSG_ALIGN(nl_na->nla_len);

    	memset(&nl_address, 0, sizeof(nl_address));
 	nl_address.nl_family = AF_NETLINK;

	len = sendto(nl_fd, (char *) &nl_request_msg, nl_request_msg.n.nlmsg_len,
  			0, (struct sockaddr *) &nl_address, sizeof(nl_address));
	if (len != nl_request_msg.n.nlmsg_len) {
		perror("sendto()");
  		close(nl_fd);
  		return -1;
    	}
    	printf("Sent to kernel: %s\n",MESSAGE_TO_KERNEL);

    	len = recv(nl_fd, &nl_response_msg, sizeof(nl_response_msg), 0);
    	if (len < 0) {
        	perror("recv()");
        	return -1;
    	}

	 //异常处理
    	if (nl_response_msg.n.nlmsg_type == NLMSG_ERROR) { //Error
        printf("Error while receiving reply from kernel: NACK Received\n");
        	close(nl_fd);
        	return -1;
    	}
    	if (len < 0) {
        	printf("Error while receiving reply from kernel\n");
        	close(nl_fd);
        	return -1;
    	}
    	if (!NLMSG_OK((&nl_response_msg.n), len)) {
        	printf("Error while receiving reply from kernel: Invalid Message\n");
        	close(nl_fd);
     		return -1;
 	}	
	
	//解析收到的来自内核的reply
    	len = GENLMSG_PAYLOAD(&nl_response_msg.n);
    	nl_na = (struct nlattr *) GENLMSG_DATA(&nl_response_msg);
    	printf("Kernel replied: %s\n",(char *)NLA_DATA(nl_na));

    	close(nl_fd);
    	return 0;
}



