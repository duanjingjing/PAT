/*************************************************************************
	> File Name: transfer_sockfd.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 16 Sep 2014 11:45:01 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>

static const int CONTROL_LEN=CMSG_LEN(sizeof(int));

/*发送文件描述符,fd参数是用来传递信息的UNIX域socket,fd_to_send参数是待发送的文件描述符*/

void send_fd(int fd,int fd_to_send){
	struct iovec iov[1];
	struct msghdr msg;
	char buf[0];

	iov[0].iov_base=buf;
	iov[0].iov_len=1;
	msg.msg_name=NULL;
	msg.msg_namelen=0;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;

	struct cmsghdr cm;
	cm.cmsg_len=CONTROL_LEN;
	cm.cmsg_level=SOL_SOCKET;
	cm.cmsg_type=SCM_RIGHTS;
	*(int*)CMSG_DATA(&cm)=fd_to_send;
	msg.msg_control=&cm;
	msg.msg_controllen=CONTROL_LEN;

	sendmsg(fd,&msg,0);
}

/*接受文件描述符*/

int recv_fd(int fd){
	struct iovec iov[1];
	struct msghdr msg;
	char buf[0];

	iov[0].iov_base=buf;
	iov[0].iov_len=1;
	msg.msg_name=NULL;
	msg.msg_namelen=0;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;

	struct cmsghdr cm;
	msg.msg_control=&cm;
	msg.msg_controllen=CONTROL_LEN;

	recvmsg(fd,&msg,0);

	int fd_to_read=*(int*)CMSG_DATA(&cm);
	return fd_to_read;
}

int main(){
    int pipefd[2];
	int fd_to_pass=0;

	//创建父子进程之间的管道,文件描述符pipefd[0]和pipefd[1]都是UNIX域套接字
	int ret=socketpair(PF_UNIX,SOCK_STREAM,0,pipefd);
	assert(ret!=-1);

	pid_t pid=fork();
	assert(pid>=0);

	if(pid==0){
		close(pipefd[0]);
		fd_to_pass=open("select.c",O_RDONLY);
		send_fd(pipefd[1],fd_to_pass);
		close(fd_to_pass);
		exit(EXIT_SUCCESS);
	}

	else{
		sleep(3);
		close(pipefd[1]);
		fd_to_pass=recv_fd(pipefd[0]);
		char buf[1024];
		memset(buf,0,1024);
		read(fd_to_pass,buf,1024);
		printf("I got fd %d and data %s\n",fd_to_pass,buf);
		close(fd_to_pass);
	}
}
