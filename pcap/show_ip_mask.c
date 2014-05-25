#include <pcap.h>
#include <stdio.h>
#include <netinet/in.h>  // in_addr
#include <arpa/inet.h>   // inet_ntoa

void show_ip_mask(char *dev){
	char errbuf[1000];
	struct in_addr addr;
	char *net_str, *mask_str;
	bpf_u_int32 net, mask;
	int err = pcap_lookupnet(dev, &net ,&mask, errbuf);
	if(err == -1){
		printf("can not get ip and mask:%s",errbuf);
		return;
	}
	
	addr.s_addr = net;
	net_str = inet_ntoa(addr);
	if(net_str == NULL){
		printf("ip trans error\n");
		return;
	}
	printf("ip : %s\n",net_str);
	addr.s_addr = mask;
	mask_str = inet_ntoa(addr);
	if(mask_str == NULL){
		printf("mask trans error\n");
		return;
	}
	printf("mask : %s\n",mask_str);
	
}

int main(){
	char *dev, errbuf[1024];
    	char select='a';
    	printf("select(dispaly the packet in detail)( Y/N ?)):");
    	scanf("%c",&select);
    	while(select!='Y'&&select!='y'&&select!='n'&&select!='N'){
        	printf("input the error!\nplease input the Y/N/y/n:");
        	scanf("%c",&select);
    	}
    
   	 //look for the net device
    	dev=pcap_lookupdev(errbuf);
    	if(dev==NULL){
        	printf("couldn't find default device: %s\n",errbuf);
        	return 1;
    	}
    	else{
        	printf("dev found success: %s\n",dev);
    	}
    
    	//ip mask display
    	show_ip_mask(dev);
    	return 0;
}

