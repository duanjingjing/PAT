/*************************************************************************
	> File Name: detach.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 08:15:35 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void* thread_func(void* arg){
	pthread_detach(pthread_self());
	printf("Hello\n");
	pthread_exit(NULL);
}

int main(int argc,const char* argv[]){
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	for(;;)
		pause();
	return 0;
}
