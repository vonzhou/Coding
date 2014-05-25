#include <pcap.h>
#include <stdio.h>

main(){
	char errBuf[PCAP_ERRBUF_SIZE], *device;
	printf("%d\n",PCAP_ERRBUF_SIZE);
	device = pcap_lookupdev(errBuf);
	if(device){
		printf("success, device:%s \n",device);
	}else{
		printf("error: %s\n",errBuf);
	}

	return 0;		
}
