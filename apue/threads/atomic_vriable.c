// learn gcc atomic variable
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <errno.h>
#include <sched.h>

#define INC_TO 1000000 // every thread adds 1 million times

int global_int = 0;

// get current thread id
pid_t gettid(void){
	return syscall(__NR_gettid);
	//return pthread_self(); // cannot work...
}

void *thread_routine(void *arg){
	int i;
	int proc_num = (int)(long)(arg);
	cpu_set_t set; // A CPU affinity mask
	
	CPU_ZERO(&set);
	CPU_SET(proc_num, &set);

	// ets the CPU affinity mask of this thread to the value specified by maski.
	//A thread's CPU affinity mask determines the set of CPUs on which it is eligible to run.
	if(sched_setaffinity(gettid(), sizeof(cpu_set_t), &set)){
		perror("sched_setaffinity");
		return NULL;
	}	

	for(i = 0; i < INC_TO; i++){
		//global_int ++ ;
		__sync_fetch_and_add(&global_int, 1);
	}	

	return NULL;
}

int main(){
	int procs = 0;
	int i;
	pthread_t *threads;
	
	//get the number of processors currently online (available).
	procs = (int)sysconf(_SC_NPROCESSORS_ONLN);   // mine is 16
	if(procs < 0){
		perror("sysconf");
		return -1;
	}

	threads = malloc(sizeof(pthread_t) * procs);
	if(threads == NULL){
		perror("malloc threads");
		return -1;
	}

	printf("Set up %d threads ....\n", procs);
	for( i = 0; i < procs ; i++){
		if(pthread_create(&threads[i], NULL, thread_routine, (void *)(long)i)){
			perror("pthread_create");
			procs = i;
			break;
		}
	}	
	
	for( i = 0; i < procs; i++){
		pthread_join(threads[i], NULL);
	}

	free(threads);
	
	printf("All threads work done.global_int is %d\n", global_int);
	printf("The expected value is %d\n" , INC_TO * procs);

	return 0;
}












