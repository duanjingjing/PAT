/*************************************************************************
	> File Name: pthread_once.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 01:33:07 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

pthread_once_t once_control=PTHREAD_ONCE_INIT;
// int pthread_once(pthread_once_t *once_control,void (*init_routine)(void));

void test_once(){
	printf("test.....\n");
}

void* thread_func(void *arg){
	//即使开启多个线程，这里也只执行一次
	pthread_once(&once_control,test_once);
	printf("In thread %lu\n",(unsigned long)pthread_self());
	return NULL;
}

int main(int argc,char *argv[]){
    
	pthread_t threads[10];

	int i;
	for(i=0;i!=10;i++){
		pthread_create(&threads[i],NULL,thread_func,NULL);
	}

	i=0;
	for(i=0;i!=10;i++){
		pthread_join(threads[i],NULL);
	}
}
