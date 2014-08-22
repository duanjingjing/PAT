/*************************************************************************
	> File Name: popen2.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:41:01 AM PDT
 ************************************************************************/

#include<stdio.h>

int main(){
	char buf[]={"aaa bbb ccc ddd eee fff ggg hhh"};
	FILE *fp=popen("wc -w","w");
	fwrite(buf,sizeof(buf),1,fp);
	pclose(fp);
	return 0;
}
