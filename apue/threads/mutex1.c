#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct foo {
	int             f_count;
	pthread_mutex_t f_lock;
	/* ... more stuff here ... */
};

struct foo *
foo_alloc(void) /* allocate the object */
{
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		/* ... continue initialization ... */
	}
	return(fp);
}

void
foo_hold(struct foo *fp) /* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void
foo_rele(struct foo *fp) /* release a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void *thr_fn1(void *pp){
	struct foo *p=(struct foo *)pp;
	printf("thread 1.......\n");
	foo_hold(p);
	pthread_exit((void*)1);
}
void *thr_fn2(void *pp){
	struct foo *p=(struct foo *)pp;
        printf("thread 2.......\n");
        foo_hold(p);
        pthread_exit((void*)2);
}
int 
main(){
	pthread_t tid1,tid2;
	void * ret1,*ret2;
	struct foo *pf;
	pf = foo_alloc();
	if(!pf)
		exit(-1);
	pthread_create(&tid1,NULL,thr_fn1,(void *)pf);
	
	pthread_join(tid1,&ret1);
	printf("main 1 : %d --\n",pf->f_count);
	pthread_create(&tid2,NULL,thr_fn2,(void *)pf);
	printf("main 2 : %d --\n",pf->f_count);

	pthread_join(tid2,&ret2);
	printf("main 3 : %d --\n",pf->f_count);

}



