/*************************************************************************
	> File Name: timeout.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 15 Sep 2014 11:06:14 PM PDT
 ************************************************************************/

#include<stdio.h>

#define TIMEOUT 5000

int timeout=TIMEOUT;
time_t start=time(NULL);
time_t end=time(NULL);

while(1){
	printf("the timeout is now %d mil_second\n",timeout);
	start=time(NULL);
	int number=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,timeout);
	if((number<0) && (errno!=EINTR)){
		printf("epoll failure\n");
		break;
	}

	if(number==0){
		timeout=TIMEOUT;
		continue;
	}

	end=time(NULL);

	/*重新计算之后的timeout值有可能等于0,说明本次epoll_wait调用返回时,不仅有文件描述符就绪,而且超时时间也刚好到达,此时我们也要处理定时任务,并重置定时时间*/

	timeout-=(end-start)*1000;
	if(timeout<=0){
		timeout=TIMEOUT;
	}
	//handle connections
}


