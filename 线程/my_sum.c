/*************************************************************************
	> File Name: my_sum.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 12:50:41 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void* my_handler(void *arg);

int main(){
	pthread_t tid;
	int a=3;
//	int a[100];
	pthread_create(&tid,NULL,my_handler,(void*)a);
	printf("create a thread: %u\n",tid);
	sleep(3);
	return 0;
}

void* my_handler(void *arg){
	int val=(int)arg;
	printf("a thread start!\n");
	printf("arg from main: %d\n",val);
	return 0;
}
