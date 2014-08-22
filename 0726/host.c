/*************************************************************************
	> File Name: host.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 25 Jul 2014 07:16:08 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<syslog.h>

int main(){
	FILE *fp;
	fp=fopen("not_here","r");
	if(!fp){
		syslog(LOG_ERR|LOG_USER,"oops- %m\n");
	}
	exit(0);
}
