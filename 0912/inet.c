/*************************************************************************
	> File Name: inet.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 07:58:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc,const char* argv[]){
	char* szValue1=inet_ntoa("1.2.3.4");
	char* szValue2=inet_ntoa("10.194.71.60");
	printf("address 1:%s\n",szValue1);
	printf("address 2:%s\n",szValue2);
}
