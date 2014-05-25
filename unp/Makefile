prifinfo:prifinfo.o sock_ntop_host.o get_ifi_info.o inet_ntop_ipv4.o
	cc -o prifinfo prifinfo.o sock_ntop_host.o get_ifi_info.o
prifinfo.o:prifinfo.c unpifi.h
	cc -c prifinfo.c
sock_ntop_host.o:sock_ntop_host.c unpifi.h
get_ifi_info.o:get_ifi_info.c unpifi.h


clean:
	rm prifinfo *.o

