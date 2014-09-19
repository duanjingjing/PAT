/*************************************************************************
	> File Name: shared_mem_chat.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 16 Sep 2014 11:02:28 PM PDT
 ************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>

#define USER_LIMIT 5
#define BUFFER_SIZE 1024
#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define PROCESS_LIMIT 65536

/*处理一个客户连接诶必要的数据*/
struct client_data{
	struct sockaddr_in address;  //客户端的socket地址
	int connfd;  //socket文件描述符
	pid_t pid;  //处理这个连接的子进程的PID
	int pipefd[2];  //和父进程通信用的管道
};

static const char* shm_name="/my_shm";
int sig_pipefd[2];
int epollfd;
int shmfd;

char* share_mem=0;
/*客户连接数组,进程用客户连接的编号来索引这个数组,即可取得相关的客户连接数据*/
client_data* users=0;
/*子进程和客户连接的映射关系表*/

int* sub_process=0;
/*当前客户数量*/
int user_count=0;
bool stop_child=false;

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

void sig_handler(int sig){
	int save_errno=errno;
	int msg=sig;
	send(pipefd[1],(char*)&msg,1,0);
	errno=save_errno;
}

void addsig(int sig,void(*handler)(int),bool restart=true){
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));

	sa.sa_handler=handler;
	(restart){
		sa.sa_flags |=SA_RESTART;
	}

	sigfillset(&sa.sa_mask);
	assert(sigaction(sig,&sa,NULL)!=-1);
}

void del_resource(){
	close(sig_pipefd[0]);
	close(sig_pipefd[1]);
	close(listenfd);
	close(epollfd);

	shm_unlink(shm_name);
	delete []users;
	delete []sub_process;
}

/*停止一个子进程*/

void child_term_handler(int sig){
	 stop_child=true;
}

/*子进程运行的函数,参数idx读出该子进程处理的客户连接的编号,users是保存所有客户连接数据的数组,参数share_mem指出共享内存的起始地址*/
int run_child(int idx,client_data* users,char* share_mem){
	epoll_event events[MAX_EVENT_NUMBER];
	/*子进程使用I/O复用技术来同时监听两个文件描述符:客户连接socket,与父进程通信的管道文件描述符*/
	int child_epollfd=epoll_create(5);
	assert(child_epollfd!=-1);

	int connfd=users[idx].connfd;
	addfd(child_epollfd,connfd);

	int pipefd=users[idx].pipefd[1];
	addfd(child_epollfd,pipefd);

	int ret;
	/*子进程需要设置自己的信号处理函数*/
	addsig(SIGTERM,child_term_handler,false);

	while(!stop_child){
		int number=epoll_wait(child_epollfd,events,MAX_EVENT_NUMBER,-1);

		if((number<0) && (errno!=EINTR)){
			printf("epoll failure\n");
			break;
		}


		for(int i=0;i<number;i++){
			int sockfd=events[i].data.fd;
			/*本子进程负责的客户连接有数据到达*/
			if((sockfd==connfd) &&  (events[i].events& EPOLLIN)){
				memset(share_mem+idx*BUFFER_SIZE,'\0',BUFFER_SIZE);
               
				/*将客户数据读取到对应的读缓存中,该读缓存是共享内存的一段,它开始于idx*BUFFER_SIZE处,长度为BUFFER_SIZE字节,因此,每个客户连接的读缓存是共享的*/
				ret=recv(connfd,share_mem+idx*BUFFER_SIZE,BUFFER_SIZE-1,0);
				if(ret<0){
					if(errno!=EAGAIN){
						stop_child=true;
					}
				}

				else if(ret==0){
					stop_child=true;
				}

				else{
					/*成功读取客户数据后就通知主进程(通过管道)来处理*/
					send(pipefd,(char*)&idx,sizeof(idx),0);
				}
			}

			/*主进程通知本进程(通过管道)将第client个客户数据发送到本进程的负责的客户端*/
			else if((sockfd==pipefd) && (events[i].events &EPOLLIN){
					int client=0;
					/*接受主进程发送来的数据,即有客户数据到达的连接的编号*/
				    ret=recv(sockfd,(char*)&client,sizeof(client),0);
				    if(ret<0){
					     if(errno!=EAGAIN){
							stop_child=true;
						 }
					}

					else if(ret==0){
					     stop_child=true;
					}

					else{
					     send(connfd,share_mem+client*BUFFER_SIZE,BUFFER_SIZE,0);

					}
			}

           else{
		      continue;
		   }
		}
	}

	close(connfd);
	close(pipefd);
	close(child_epollfd);
	return 0;
}
