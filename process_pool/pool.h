/*************************************************************************
	> File Name: pool.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 06:00:42 AM PDT
 ************************************************************************/

#ifndef _POOL_H_
#define _POOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define S_BUSY 1
#define S_IDLE 0

typedef struct sockaddr_in SA;

typedef struct tag{
	pid_t s_pid;
	int s_flag;
	int s_read;
	int s_write;
	int s_cnt;
}CHLD,*pCHLD;

int make_child(pCHLD arr,int cnt);
#endif

