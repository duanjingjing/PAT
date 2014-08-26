/*************************************************************************
	> File Name: my_thread_share.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 01:05:40 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int cnt=0;
pthread_mutex_t my_mutex;

void *my_handler(void* arg){
	int index;
	for(index=0;index<10000;index++){
		pthread_mutex_lock(&my_mutex);
		printf("get a lock: %u\n",pthread_self());
		cnt++;
		pthread_mutex_unlock(&my_mutex);
	}
}

int main(){
	pthread_mutex_init(&my_mutex,NULL);
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,my_handler,NULL);
	pthread_create(&tid2,NULL,my_handler,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("cnt: %d\n",cnt);
	pthread_mutex_destroy(&my_mutex);
	return 0;
}
