/*************************************************************************
	> File Name: produce_consume.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 01:45:39 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 20
int queue[N];
int front,rear;
pthread_cond_t produce_cond,consum_cond;
pthread_mutex_t queue_mutex;
int left_cnt,produce_cnt;
void* producer(void* arg);
void* consumer(void* arg);

int main(int argc,char* argv[]){ //exe pro_num con_num
	front=-1;
	rear=0;
	left_cnt=20;
	produce_cnt=0;
	int pro_num=atoi(argv[1]);
	int con_num=atoi(argv[2]);

	srand(getpid());
	pthread_mutex_init(&queue_mutex,NULL);
	pthread_cond_init(&produce_cond,NULL);
	pthread_cond_init(&consum_cond,NULL);
	pthread_t tid1,tid2;
	while(pro_num>0){
		pthread_create(&tid1,NULL,producer,NULL);
		pro_num--;
	}

	while(con_num>0){
		pthread_create(&tid2,NULL,consumer,NULL);
		con_num--;
	}

	while(1);
	pthread_mutex_destroy(&queue_mutex);
	pthread_cond_destroy(&produce_cond);
	pthread_cond_destroy(&consum_cond);
}

void* producer(void* arg){
	pthread_detach(pthread_self());
	while(1){
		pthread_mutex_lock(&queue_mutex);

		while(left_cnt==0){
			pthread_cond_wait(&produce_cond,&queue_mutex);
		}

		printf("a producer in! current produce:%d \n",produce_cnt);
		produce_cnt++;
		if(produce_cnt==1){//signal consumer to consum
			pthread_cond_broadcast(&consum_cond);
		}

		left_cnt--;
		printf("a producer out! current produce: %d\n",produce_cnt);
		pthread_mutex_unlock(&queue_mutex);
		sleep(rand()%5+1);
	}
}

void* consumer(void* arg){
	pthread_detach(pthread_self());
	while(1){
		pthread_mutex_lock(&queue_mutex);
		while(produce_cnt==0){
			pthread_cond_wait(&consum_cond,&queue_mutex);
		}

       printf("a consumer in,current products: %d\n",produce_cnt);
	   left_cnt++;

	   if(left_cnt==1){
		   pthread_cond_broadcast(&produce_cond);
	   }

	   produce_cnt--;

	   printf("a consumer out,current products: %d\n",produce_cnt);
	   pthread_mutex_unlock(&queue_mutex);
	   sleep(rand()%5+1);
	}
}

