/*************************************************************************
	> File Name: sendfile.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 06:57:11 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(int argc,char* argv[]){
	if(argc<=3){
		printf("usage:%s ip_address port_number filename\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);
	const char* file_name=argv[3];

	int filefd=open(file_name,O_RDONLY);
	assert(filefd>0);

	struct stat stat_buf;
	fstat(filefd,&stat_buf);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	inet_pton(ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sock=socket(PF_INET,SOCK_STREAM,0);
	assert(sock>=0);

	int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret>=0);

	ret=listen(sock,5);
	assert(ret!=-1);

	struct sockaddr_in client;
	socklen_t addrlen=sizeof(client);

	int connfd=accept(sock,(struct sockaddr*)&client,&addrlen);
	if(connfd<0){
		printf("errno is:%s\n",errno);
	}
	else{
       sendfile(connfd,filefd,NULL,stat_buf.st_size);
	   close(connfd);
	}
	close(sock);
	return 0;
}
