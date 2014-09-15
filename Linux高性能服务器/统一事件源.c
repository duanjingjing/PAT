/*************************************************************************
	> File Name: 统一事件源.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 14 Sep 2014 11:45:19 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>


#define MAX_EVENT_NUMBER 1024
static int pipefd[2];

int setnonblocking(int fd){
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

void addfd(int epollfd,int fd){
    epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN | EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}


/*信号处理函数*/
void sig_handler(int sig){
	/*保留原来的errno,在函数最后恢复,以保证函数的可重入性*/
	int save_errno=errno;
	int msg=sig;
	send(pipefd[1],(char*)&msg,1,0);//将信号写入管道,以通知主循环
	errno=save_errno;
}

/*设置信号的处理函数*/
void addsig(int sig){
    struct sigaction sa;
	sa.sa_handler=sig_handler;
	sa.sa_flags|=SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig,&sa,NULL)!=-1);
}

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage: %s ip_address port_number\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);

	int listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(listenfd,5);
	assert(ret!=-1);

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd=epoll_create(5);
	assert(epollfd!=-1);
	addfd(epollfd,listenfd);

	/*使用socketpair函数创建管道,注意pipefd[0]上的可读事件*/
	ret=socketpair(PF_UNIX,SOCK_STREAM,0,pipefd);
	assert(ret!=-1);
	setnonblocking(pipefd[1]);
	addfd(epollfd,pipefd[0]);

	/*设置一些信号处理函数*/
	addsig(SIGHUP);
	addsig(SIGCHLD);
	addsig(SIGTERM);
	addsig(SIGINT);
	bool stop_server=false;

	while(!stop_server){
		int number=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
		if((number<0) && (errno!=EINTR)){
			printf("epoll error\n");
			break;
		}

		for(int i=0;i<number;i++){
			int sockfd=events[i].data.fd;
			/*如果就绪的文件描述符是listenfd,则处理新的连接*/
			if(sockfd==listenfd){
				struct sockaddr_in peerAddress;
				bzero(&peerAddress,sizeof(peerAddress));
				socklen_t len=sizeof(peerAddress);

				int connfd=accept(sockfd,(struct sockaddr*)&peerAddress,
						&len);

				addfd(epollfd,connfd);
			}

			/*如果就绪的文件描述符是pipefd[0]，则处理信号*/
			else if(sockfd==pipefd[0] && (events[i].events & EPOLLIN)){
				 int sig;
				 char signals[1024];
				 ret=recv(pipefd[0],signals,1024,0);
				 if(ret==-1){
					 continue;
				 }

				 else if(ret==0){
					 continue;
				 }

				 else{
					 /*因为每个信号值占1个字节,所以按字节来逐个接受信号*/
                     for(int i=0;i<ret;i++){
						 switch(signals[i]){
                            case SIGCHLD:
							case SIGHUP:
							{
								continue;
							}

							case SIGTERM:
							case SIGINT:
							{
								printf("recv SIGINT!\n");
								stop_server=true;
							}
						 }
					 }
				 }
			}

			else{
			}
		}
	}

	printf("close fds\n");
	close(listenfd);
	close(pipefd[1]);
	close(pipefd[0]);
	return 0;
}






