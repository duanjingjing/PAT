/*************************************************************************
	> File Name: tcp2.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 02:07:52 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number recv_buffer\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));

	address.sin_family=AF_INET;
	address.sin_port=htons(port);
    inet_pton(PF_INET,ip,&address.sin_addr);

	int sock=socket(PF_INET,SOCK_STREAM,0);
	assert(sock!=-1);

	int recvbuf=atoi(argv[3]);
	int len=sizeof(recvbuf);

	/*先设置TCP接受缓冲区的大小,然后立即读取*/
	setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&recvbuf,sizeof(recvbuf));
	getsockopt(sock,SOL_SOCKET,SO_RCVBUF,&recvbuf,(socklen_t*)&len);

	int ret=bind()
    
}
