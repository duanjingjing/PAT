/*************************************************************************
	> File Name: http.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 05:11:24 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
static const char* status_line[2]={"200 OK","500 Internal server error"};

int main(int argc,const char* argv[]){
	if(argc<=3){
		printf("usage:%s ip_address port_number filename\n".argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);
    const char* file_name=argv[3];

	struct sockaddr_in address;
	address.sin_family=AF_INET;
	inet_pton(PF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sock=socket(AF_INET,SOCK_STREAM,0);
    assert(sock!=-1);

	int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	struct sockaddr_in peerAddr;
	socklen_t addrlen=sizeof(peerAddr);
	bzero(&peerAddr,sizeof(peerAddr));

	int connfd=accept(sock,(struct sockaddr*)&peerAddr,&addrlen);
	if(connfd==-1){
		perror("accept");
		return -1;
	}

    else{
		/*用于保存HTTP应答的状态行、头部字段和一个空行的缓冲区*/
		char header_buf[BUFFER_SIZE];
		memset(header_buf,'\0',BUFFER_SIZE);
		/*用于存放目标文件内容的应用程序缓存*/
		char* file_buf;
		/*用于获取目标文件的属性,比如是否为目录、文件大小等*/
		struct stat file_stat;
        /*记录目标文件是否是有效文件*/
		bool valid=true;
		/*缓存区header_buf目前已经使用了多少字节的空间*/
		int len=0;
		if(stat(file_name,&file_stat)<0){
			valid=false;
		}

		else{
			if(S_ISDIR(file_stat.st_mode)){
				valid=false;
			}

			else if(file_stat.st_mode & S_IROTH){//当前用户有读取目标文件的权限*/
				int fd=open(file_name,O_RDONLY);
				if(fd==-1){
					perror("open");
					return -1;
				}

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
			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"Content-Length:%d\r\n",file_stat.st_size);
			len+=ret;

			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"%s","\r\n");
			/*利用writev和header_buf和file_buf的内容一并写出*/
			struct iovec iv[2];
			iv[0].iov_base=header_buf;
			iv[0].iov_len=strlen(header_buf);
			iv[1].iov_base=file_buf;
			iv[1].iov_len=file_stat.st_size;
			ret=writev(connfd,iv,2);
		}

		else{//如果目标文件无效,则通知客户端服务器发生了错误
			ret=snprintf(header_buf,BUFFER_SIZE-1,"%s %s\r\n",
					"HTTP/1.1",status_line[1]);
			len+=ret;
			ret=snprintf(header_buf+len,BUFFER_SIZE-1-len,"%s","\r\n");
			send(connfd,header_buf,strlen(header_buf),0);
		}

		close(connfd);
		delete []file_buf;
	}
	close(sock);
	return 0;
}

