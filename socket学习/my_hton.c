/*************************************************************************
	> File Name: my_hton.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 02:30:48 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HTON(ip) \
	(ip&(unsigned int)0xff)<<24 |\
    (ip&((unsigned int)0xff <<8))<<8 |\
    (ip&((unsigned int)0xff <<16))>>8 |\
    (ip& ((unsigned int)0xff <<24))>>24

char* ntoa(int ip);

int main(int argc,char* argv[]){
	char *ip=argv[1];
	int a[4];
	sscanf(ip,"%d.%d.%d.%d",&a[0],&a[1],&a[2],&a[3]);
	int my_host=(a[0]<<24) | (a[1]<<16) | (a[2]<<8) | a[3];
	int my_net=HTON(my_host);
	printf("my_host: %x\n my_netword:%x\nip:%s\n",my_host,my_net,ntoa(my_host));
	return 0;
}

char* ntoa(int ip){
	char* str=(char*)calloc(16,1);
	sprintf(str,"%d.%d.%d.%d",(ip&(0xff000000))>>24,(ip&(0x00ff0000))>>16
			(ip&(0x0000ff00))>>8)
}
