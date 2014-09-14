/*************************************************************************
	> File Name: 聊天室_server.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 14 Sep 2014 12:42:51 AM PDT
 ************************************************************************/
#define _GNU_SOURCE 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>

#define USER_LIMIT 5 //最大用户数量
#define BUFFER_SIZE 64 //缓冲区的大小
#define FD_LIMIT 65535  //文件描述符的数量限制

/*客户数据:客户端socket地址,待写到客户端的数据位置,从客户端读入的数据*/
struct client_data{
	struct sockaddr_in address;
	char* write_buf;
	char buf[BUFFER_SIZE];
};


int setnonblocking(int fd){
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip port\n",argv[0]);
		exit(-1);
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(listenfd,5);
	assert(ret!=-1);

	client_data *users=new client_data[FD_LIMIT];

	int user_count=0;
	pollfd fds[USER_LIMIT+1];

	for(int i=0;i<USER_LIMIT+1;i++){
		fds[i].fd=-1;
		fds[i].revents=0;
	}

	fds[0].fd=listenfd;
	fds[0].events=POLLIN | POLLERR;
	fds[0].revents =0;

	while(1){
        ret=poll(fds,user_count+1,-1);
		if(ret<0){
			printf("poll failure\n");
			break;
		}
		for(int i=0;i<user_count+1;i++){
			if((fds[i].fd==listenfd) && (fds[i].revents & POLLIN)){
				struct sockaddr_in client_address;
				bzero(&client_address,sizeof(client_address));
				socklen_t addrlen=sizeof(client_address);

				int connfd=accept(listenfd,(struct sockaddr*)&client_address,&addrlen);

				if(user_count>=USER_LIMIT){
					const char* info="too many users";
					printf("%s\n",info);

					send(connfd,info,strlen(info),0);
					close(connfd);
					continue;
				}

				user_count++;
				users[connfd].address=client_address;
                fds[user_count].fd=connfd;
				fds[user_count].events=POLLIN | POLLRDHUP | POLLERR;
				fds[user_count].revents =0;

				printf("comes a new user,now have %d users\n",user_count);
			}
          
			else if(fds[i].revents & POLLERR){
				printf("get an error from %d\n",fds[i].fd);
				int error=0;
				socklen_t length=sizeof(error);
				if(getsockopt(fds[i].fd,SOL_SOCKET,SO_ERROR,&error,&length)<0){
					printf("get socket option failed\n");
				}

				continue;
			}

			else if(fds[i].revents & POLLRDHUP){
				/*如果客户端关闭连接，则服务器也关闭连接，并将用户数减1*/
				users[fds[i].fd]=users[fds[user_count].fd];
				close(fds[i].fd);
				fds[i]=fds[user_count];
				i--;
				user_count--;
				printf("a client left\n");
			}

			else if(fds[i].revents & POLLIN){
				int connfd=fds[i].fd;
				memset(users[connfd].buf,'\0',BUFFER_SIZE);

                ret=recv(connfd,users[connfd].buf,BUFFER_SIZE-1,0);
				printf("get %d bytes of client data %s from %d\n",ret,
						users[connfd].buf,connfd);

				if(ret<0){
					//如果读操作出错,则关闭连接*/
					if(errno!=EAGAIN){
						close(connfd);
						users[fds[i].fd]=users[fds[user_count].fd];
                        fds[i]=fds[user_count];
						i--;
						user_count--;
					}
				}

				else if(ret==0){
				}

				else{
					/*如果接受到客户数据,则通知其他socket连接准备写数据*/
					for(int j=1;j<=user_count;j++){
						if(fds[j].fd==connfd) {
							continue;
						}

						fds[j].events |=~POLLIN;
						fds[j].events |=POLLOUT;
						users[fds[j].fd].write_buf=users[connfd].buf;
					}

				}
			}

			else if(fds[i].revents & POLLOUT){
				int connfd=fds[i].fd;
				if(!users[connfd].write_buf){
					continue;
				}

                ret=send(connfd,users[connfd].write_buf,strlen(users[connfd].write_buf),0);
				users[connfd].write_buf=NULL;

				/*写完数据后需要重新注册fds[i]上的可读事件*/
				fds[i].events |=~POLLOUT;
				fds[i].events |=POLLIN;
			}
           
		}
	}

	delete []users;
	close(listenfd);
	return 0;
}

