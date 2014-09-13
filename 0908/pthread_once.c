/*************************************************************************
	> File Name: pthread_once.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 08:18:04 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_once_t once_control=PTHREAD_ONCE_INIT;

void test_once(){
	printf("test.....\n");
}

void* thread_func(void* arg){
	pthread_once(&once_control,test_once);

	printf("In thread %lu\n",(unsigned long)pthread_self());
	return NULL;
}

int main(int argc,const char* argv[]){
	pthread_t threads[10];

	int i;
	for(i=0;i!=10;i++){
		pthread_create(&threads[i],NULL,thread_func,NULL);
	}

	i=0;
	for(i=0;i!=10;i++){
		pthread_join(threads[i],NULL);
	}

	return 0;
}
