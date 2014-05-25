#include <pcap.h>
#include <time.h>
#include <stdio.h>

void capture_pkt1(pcap_t *dev){
	struct pcap_pkthdr packet;
	char errbuf[1024];
	// capture
	const u_char *pkt = pcap_next(dev, &packet);
	if(!pkt){
		printf("can not capture packet,%s\n",errbuf);
		return;
	}
	
	// output the pket info
	printf("Packet len: %d\n",packet.len);
	printf("Number of bytes in pkt: %d\n",packet.caplen);
	printf("Recv time: %s\n",ctime((const time_t *)&packet.ts.tv_sec));
}

int main()
{
    	char *dev, errbuf[1024];
    
    	//look for the net device
    	dev=pcap_lookupdev(errbuf);
    	if(dev==NULL){
        	printf("couldn't find default device: %s\n",errbuf);
        	return 1;
    	}
    	else{
        	printf("found dev success: %s\n",dev);
    	}
    
    	//open the dev(must set corresponding ethx  promisc)
    	pcap_t* device=pcap_open_live(dev,65535,1,0,errbuf);
    	if(!device){
        	printf("couldn't open the net device: %s\n",errbuf);
        	return 1;
    	}
	// just sniffer the next packet
        while(1){
		capture_pkt1(device); 
	}
    	return 0;
}

