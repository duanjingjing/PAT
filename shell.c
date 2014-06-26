/*************************************************************************
	> File Name: shell.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 25 Jun 2014 06:28:23 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define N 100
#define Shell_Name  "xuejun@ubuntu:~$" 

void  trim_space(char *str){
     char *p=str;
	 int size=0;

	 while(1){
		 while(*p==' ' && *p!='\n') p++;
		 if(*p=='\n') break;

		 while(*p!=' ' && *p!='\n'){
			str[size++]=*p;
			p++;
			
		 }
		 if(*p=='\n') break;

		 str[size++]=' ';
	 }
	 str[size]=0;
}


int main(int argc,char *argv[]){
	char buf[1024],str[100];

	while(1){
        printf("%s",Shell_Name);
        while(fgets(buf,1024,stdin)!=EOF && buf[0]!='\n'){
		     printf("%s",Shell_Name);
             trim_space(buf);
             if(strcmp(buf,"exit")==0){
				 exit(-1);
			 }
			 else{
				 int num_words=0;
				 int i;
				 for(i=0;i<strlen(buf);i++){
					 if(buf[i]==' ')
						 num_words++;
				 }

				 num_words+=1;
				 char **args=(char**)malloc(sizeof(char*)*(num_words+1));

				 char *p=buf;
				 for(i=0;i<num_words;i++){
					 memset(str,0,sizeof(str));
					 int j=0;
					 while(*p!=' ' && *p!='\0'){
						 str[j]=*p;
						  p++;
						 j++;
					 }

					 str[j]=0;
					 *(args+i)=(char*)malloc(sizeof(char)*j);
					 strcpy(*(args+i),str);
					 if(*p==' ') p++;
				 }

			   *(args+num_words)=(char*)malloc(sizeof(char)*2);
		
			    *(args+num_words)=NULL;
				 int ret=fork();
				 if(ret){
					  wait(NULL);
				 }

				 else{
				  execvp(args[0],args);
				 }
			}
		}
	}
	return 0;
}
