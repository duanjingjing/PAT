/*************************************************************************
	> File Name: select.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 02:23:26 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		exit(-1);
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(PF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int fd=socket(AF_INET,SOCK_STREAM,0);
	assert(fd!=-1);

	ret=bind(fd,(struct sockaddr*)&address,sizeof(address));
	if(ret==-1){
		perror("bind");
		exit(-1);
	}

	ret=listen(fd,5);
	assert(ret!=-1);

	struct sockaddr_in peerAddress;
	bzero(&peerAddress,sizeof(peerAddress));
	socklen_t addrlen=sizeof(peerAddress);

	int connfd=accept(fd,(struct sockaddr*)&peerAddress,&addrlen);
	if(connfd<0){
		printf("errno");
		close(fd);
	}

	printf("peer ip:%s and port:%d\n",inet_ntoa(peerAddress.sin_addr),ntohs(peerAddress.sin_port));

	char buf[1024];
	fd_set read_fds,exception_fds;
	FD_ZERO(&read_fds);
	FD_ZERO(&exception_fds); 

	while(1){
		FD_SET(connfd,&read_fds);
		FD_SET(connfd,&exception_fds);

		ret=select(connfd+1,&read_fds,NULL,&exception_fds,NULL);
		if(ret<0){
			printf("selection failure!\n");
			break;
		}

		if(FD_ISSET(connfd,&read_fds)){
			int nread=recv(connfd,buf,sizeof(buf)-1,0);
			if(nread<=0){
               break;
			}

			printf("get %d bytes of normal data:%s",nread,buf);
		}

		if(FD_ISSET(connfd,&exception_fds)){
		    ret=recv(connfd,buf,sizeof(buf),0);
			if(ret<=0){
				break;
			}

			printf("get %d bytes of oob data:%s",ret,buf);
		}
	}

	close(connfd);
	close(fd);
	return 0;
}
