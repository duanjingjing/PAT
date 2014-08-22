/*************************************************************************
	> File Name: thread_pool.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 01:17:10 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)


void *thread_func(void *arg){
	printf("Test.......\n");
	pthread_t tid=pthread_self();
	printf("tid=%ld\n",(unsigned long)tid);

	pthread_exit((void*)100);
	printf("Test 2......\n");
	return NULL;
}

int main(){
	pthread_t tid;
	int status;
    pthread_create(&tid,NULL,thread_func,NULL);
	pthread_join(tid,(void**)&status);
	printf("pthread exit code =%d\n",status);
	return 0;
}
