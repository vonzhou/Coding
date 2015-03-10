#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_cond_t ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int flag = 0;


void *thread_func(void *arg){
    int i;
    for(i =0; i<50;i++){
        pthread_mutex_lock(&lock);
        if(flag!=0)
            pthread_cond_wait(&ready, &lock);
        int j;
        for(j=0;j<10;j++)
            printf("A");
        printf("\n");
        flag++;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&ready);
    }
}

int main(){
    pthread_t tid;
    int res,i;
    if((res = pthread_create(&tid, NULL, thread_func, NULL)) != 0){
        printf("pthread create error\n");
        exit(-1);
    }

    for(i=0; i<50; i++){
        pthread_mutex_lock(&lock);
        if(flag!=1)
            pthread_cond_wait(&ready, &lock);
        int j;
        for(j=0; j<100;j++)
            printf("B");
        printf("\n");
        flag--;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&ready);
    }
    
    pthread_join(tid, NULL);

    return 0;
}
