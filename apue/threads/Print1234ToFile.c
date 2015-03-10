#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cur =0;   // 通过改变cur来调节输出的顺序
char content[4] = {'1', '2', '3', '4'};
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
        cur = (cur+1)%4;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&ready);
    }


}

int main(int argc, char **argv){
    pthread_t tid[4];
    int res ;
    int i;
    if(argc != 2){
        printf("usage : a.out how\n");
        exit(-1);
    }
    cur = atoi(argv[1]);

    for(i=0;i<4;i++){
        res = pthread_create(&tid[i],NULL,thread_func,(void *)i);
        if(res != 0)
            exit(-1);

    }
    for(i=0;i<4;i++){
        pthread_join(tid[i], NULL);
    }
    printf("\n");
    return 0;
}
