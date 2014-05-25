#include<stdlib.h>
#include<stdio.h>

#include<event.h>

struct event ev;
struct timeval tv;

void time_cb(int fd,short event,void *arg){
	printf("timer wakeup\n");
	event_add(&ev,&tv);//重新调度，类似于信号处理/中断函数
}

int main(){
	struct event_base *base = event_base_new();
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	evtimer_set(&ev,time_cb,NULL);
	event_base_set(base,&ev);
	event_add(&ev,&tv);
	event_base_dispatch(base);
}
