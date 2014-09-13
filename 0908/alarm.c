/*************************************************************************
	> File Name: alarm.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:24:36 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void handle(int Signum){
	 time_t tt;
	 time(&tt);

	 struct tm* pTm=gmtime(&tt);
	 printf("%04d-%02d-%02d  %02d:%02d:%02d\n",(1900+pTm->tm_year),
			 (1+pTm->tm_mon),pTm->tm_mday,(8+pTm->tm_hour),pTm->tm_min,
			 pTm->tm_sec);
}

void init(int tv_sec,int tv_usec){
	signal(SIGALRM,handle);

	struct itimerval tm;
	tm.it_value.tv_sec=tv_sec;
	tm.it_value.tv_usec=tv_usec;

	tm.it_interval.tv_sec=tv_sec;
	tm.it_interval.tv_usec=tv_usec;

	int ret;
	if((ret=setitimer(ITIMER_REAL,&tm,NULL))==-1){
		perror("setitimer");
		exit(EXIT_FAILURE);
	}
}

int main(int argc,const char* argv[]){
	init(1,0);

	while(1);
}
