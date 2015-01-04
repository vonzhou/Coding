#include <linux/wait.h>
/*	wake_up_interruptible()
*/
#include <net/sock.h>
/*	struct sock{}
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
/*	skb_recv_datagram()
*/

#define NETLINK_TEST 23

struct sock *nl_sk = NULL;

void nl_data_ready (struct sk_buff *skb)
{
		//wake_up_interruptible(&(sk->wait));
		wake_up_interruptible(sk_sleep(skb->sk));
}

void netlink_test() {
		struct sk_buff *skb = NULL;
		struct nlmsghdr *nlh = NULL;
		int err;
		u32 pid;
		
		//nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST,	nl_data_ready);
		struct netlink_kernel_cfg cfg = {
			.input = nl_data_ready,
		};
		nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST,	&cfg);
		if(!nl_sk){
			printk(KERN_ALERT "netlink kernel create error\n");
			return -1;
		}

		/* wait for message coming down from user-space */
		skb = skb_recv_datagram(nl_sk, 0, 0, &err);
		if(!skb)
			printk(KERN_INFO "info from user space..\n");
		nlh = (struct nlmsghdr *)skb->data;
		printk("%s: received netlink message payload:%s\n", __FUNCTION__, NLMSG_DATA(nlh));

		pid = nlh->nlmsg_pid; /*pid of sending process */
		NETLINK_CB(skb).dst_group = 0;
		//NETLINK_CB(skb).portid = 0;      /* from kernel */
		//NETLINK_CB(skb).dst_pid = pid;
		//NETLINK_CB(skb).dst_groups = 0;  /* unicast */
		// echo to userspace
		//netlink_unicast(nl_sk, skb, pid, MSG_DONTWAIT);
		//...netlink_unicast(struct sock *ssk, struct sk_buff *skb, u32 portid, int nonblock)
		nlmsg_unicast(nl_sk, skb, pid);
		//sock_release(nl_sk->socket);
}


static int __init lkp_init(void)
{
		netlink_test();
		return 0;
}

static void __exit lkp_cleanup(void)
{
		netlink_kernel_release(nl_sk);
		printk("<2> goodbye, leaving kernel space...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


