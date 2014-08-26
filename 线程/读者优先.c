/*************************************************************************
	> File Name: read_first.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 01:14:35 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>

int read_cnt=0;
int write_flag=1;//write permit
pthread_mutex_t read_cnt_mutex,access_mutex,write_flag_mutex;
int cnt=3;

void* write_handler(void* arg);
void* read_handler(void* arg);

int main(){
	int type;
	srand(getpid());
	pthread_mutex_init(&read_cnt_mutex,NULL);
	pthread_mutex_init(&access_mutex,NULL);
	pthread_mutex_init(&write_flag_mutex,NULL);

	while(1){
		type=rand();
		if(type%2==0){
			pthread_t tid;
			pthread_create(&tid,NULL,write_handler,NULL);
		}
		else{
			pthread_t tid;
			pthread_create(&tid,NULL,read_handler,NULL);
		}
		sleep(1);
	}

	pthread_mutex_destroy(&read_cnt_mutex);
	pthread_mutex_destroy(&access_mutex);
	pthread_mutex_destroy(&write_flag_mutex);
}

void* write_handler(void* arg){
     pthread_detach(pthread_self());

	 pthread_mutex_lock(&access_mutex);
	 printf("a writer in before:%d\n",cnt);
	 cnt++;
	 sleep(5);
	 printf("a write out after:%d \n",cnt);

	 pthread_mutex_unlock(&access_mutex);
}

void* read_handler(void* arg){
	pthread_detach(pthread_self());

	pthread_mutex_lock(&read_cnt_mutex);
	if(read_cnt==0){
		pthread_mutex_lock(&access_mutex);
	}

	read_cnt++;
	pthread_mutex_unlock(&read_cnt_mutex);
    
	printf("a reader in,id:%u, cnt value:%d\n",pthread_self(),cnt);
	sleep(3);

	pthread_mutex_lock(&read_cnt_mutex);
	read_cnt--;
	printf("a reader leave!id:%u,  reader left: %d\n",pthread_self(),read_cnt);
	if(read_cnt==0){
		pthread_mutex_unlock(&access_mutex);
	}
	pthread_mutex_unlock(&read_cnt_mutex);
}

