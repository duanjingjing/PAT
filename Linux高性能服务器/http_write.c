/*************************************************************************
	> File Name: http_write.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 18 Sep 2014 02:58:33 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


#define BUFFER_SIZE 1024
static const char* status_line[2]={"200 Ok","500 Internal terminate"};

//定义两种HTTP状态码和状态信息
int main(int argc,char* argv[]){
	if(argc<=3){
		printf("usage:%s ip_address port_number filename\n",argv[0]);
		exit(-1);
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	const char* filename=argv[3];
    struct sockaddr_in address;
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd>=0);

	int ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

    ret=listen(sockfd,5);
	assert(ret!=-1);

    struct sockaddr_in client_address;
	bzero(&client_address,sizeof(client_address));
	socklen_t len=sizeof(client_address);

	int connfd=accept(sockfd,(struct sockaddr*)&client_address,&len);
	if(connfd<0){
		printf("errno is: %d\n",errno);
	}

	else{
		char header_buf[BUFFER_SIZE];
		memset(header_buf,'\0',BUFFER_SIZE);
		char *file_buf;

		struct stat file_stat;
		bool valid=true;
		int len=0;
		if(stat(filename,&file_stat)<0){
			valid=false;
		}

		else{
			if(S_ISDIR(file_stat.st_mode)){
				valid=false;
			}

			else if(file_stat.st_mode & S_IROTH){
				int fd=open(filename,O_RDONLY);
				file_buf=new char[file_stat.st_size+1];
				memset(file_buf,'\0',file_stat.st_size+1);
				if(read(fd,file_buf,file_stat.st_size)<0){
					valid=false;
				}
			}

			else{
				valid=false;
			}
		}


		if(valid){
			ret=snprintf(header_buf,BUFFER_SIZE-1,"%s %s\r\n","HTTP/1.1",status_line[0]);
			len+=ret;
			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"Content-Length:%d \r\n",(int)file_stat.st_size);
			len+=ret;
			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"%s","\r\n");
			struct iovec iv[2];

			iv[0].iov_base=header_buf;
			iv[0].iov_len=strlen(header_buf);
			iv[1].iov_base=file_buf;
			iv[1].iov_len=file_stat.st_size;
			ret=writev(connfd,iv,2);
		}

		else{
			ret=snprintf(header_buf,BUFFER_SIZE-1,"%s %s\r\n",
					"HTTP/1.1",status_line[1]);
			len+=ret;
			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"%s","\r\n");
			send(connfd,header_buf,strlen(header_buf),0);
		}

		close(connfd);
		delete [] file_buf;
	}

	close(sockfd);
	return 0;
}

