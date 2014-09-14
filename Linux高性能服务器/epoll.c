/*************************************************************************
	> File Name: epoll.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 03:45:58 AM PDT
 ************************************************************************/

#include<stdio.h>

/*如何索引poll返回的就绪文件描述符*/

int ret=poll(fds,MAX_EVENT_NUMBER,-1);
/*必须遍历所有已注册文件描述符并找到其中就绪者*/
for(int i=0;i<MAX_EVENT_NUMBER;i++){
	if(fds[i].revents & POLLIN){
		int sockfd=fds[i].fd;
		/*处理sockfd*/
	}
}

/*如何索引epoll返回的就绪文件描述符*/

int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
/*仅遍历就绪的ret个文件描述符*/
for(int i=0;i<ret;i++){
	int sockfd=events[i].data.fd;
	/*socket肯定就绪，直接处理*/
}


