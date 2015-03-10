#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cur =0;
char content[3] = {'A', 'B', 'C'};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready = PTHREAD_COND_INITIALIZER;

void *thread_func(void *arg){
    int x = (int)arg;
    int i;
    //printf("lsldf\n");
    for(i=0; i<10;i++){
        pthread_mutex_lock(&lock);
        while(x != cur)
            pthread_cond_wait(&ready, &lock);
        printf("%c", content[cur]);
        cur = (cur+1)%3;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&ready);
    }


}

int main(){
    pthread_t tid[3];
    int res ;
    int i;
    for(i=0;i<3;i++){
        res = pthread_create(&tid[i],NULL,thread_func,(void *)i);
        if(res != 0)
            exit(-1);

    }

    for(i=0;i<3;i++){
        pthread_join(tid[i], NULL);
    }
    return 0;
}
