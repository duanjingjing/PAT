/*************************************************************************
	> File Name: daytime.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 04:42:59 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <assert.h>

int main(int argc,const char* argv[]){
	assert(argc==2);
	char* host=argv[1];
	/*获取目标主机地址信息*/
	struct hostent* hostinfo=gethostbyname(host);
	assert(hostinfo);

	/*获取daytime服务信息*/
	struct servent* servinfo=getservbyname("daytime","tcp");
	assert(servinfo);
	printf("daytime port is %d\n",ntohs(servinfo->s_port));

	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=servinfo->s_port;

	address.sin_addr=*(struct in_addr*)*hostinfo->h_addr_list;


}
