/*************************************************************************
	> File Name: hostget.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 25 Jul 2014 07:11:37 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/utsname.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	char computer[256];
	struct utsname uts;

	if(gethostname(computer,255)!=0 || uname(&uts)<0){
		fprintf(stderr,"Could not get host ubformation\n");
		exit(1);
	}

	printf("Computer host name is %s\n",computer);
	printf("System is %s on %s hardware\n",uts.sysname,uts.machine);
	printf("Nodename is %s\n",uts.nodename);
	printf("Version is %s,%s\n",uts.release,uts.version);
	exit(0);
}
