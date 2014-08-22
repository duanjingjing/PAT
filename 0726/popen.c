/*************************************************************************
	> File Name: popen.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:38:12 AM PDT
 ************************************************************************/

#include<stdio.h>

int main(){
	FILE *fp=popen("cat /etc/profile","r");
	if(!fp){
		perror("popen");
		exit(-1);
	}

	char buf[512]={0};
	while(fgets(buf,512,fp)){
		puts(buf);
	}
	pclose(fp);
    return 0;
}
