/*************************************************************************
	> File Name: http_有限状态机.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 12:38:07 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096 /*读缓冲区大小*/

/*主状态机的两种可能状态,分别表示:当前正在分析请求行,当前正在分析头部字段 */
enum CHECK_STATE(CHECK_STATE_REQUESTLINE=0,CHECK_STATE_HEADER);
/*从状态机的三种可能状态,即行的读取状态，分别表示:读取到一个完整的行,行出错和行数据尚且不完整*/
enum LINE_STATUS(LINE_OK=0,LINE_BAD,LINE_OPEN);
/*服务器处理HTTP请求的结果:NO_REQUEST表示请求不完整,需要继续读取客户数据;GET_REQUEST表示获得了一个完整的客户请求*/
enum HTTP_CODE {NO_REQUEST,GET_REQUEST,BAD_REQUEST，FORBIDDEN_REQUEST,
	INTERNAL_ERROR,CLOSED_CONNECTION};

static const char* szret[]={"I get a correct result\n","Something wrong\n"};


LINE_STATUS parse_line(char* buffer,int& checked_index,int& read_index){
     char temp;
	 for(;checked_index<read_index;checked_index++){
         /*获得当前要分析的字节*/
		 temp=buffer[checked_index];
		 if(temp=='\r'){
			 if((checked_index+1)==read_index){
				 return LINE_OPEN;
			 }
             else if(buffer[checked_index+1]=='\n'){
				 buffer[checked_index++]='\0';
				 buffer[checked_index++]='\0';
				 return LINE_OK;
			 }
             return LINE_BAD;
		 }

		 else if(temp=='\n'){
			 if((checked_index>1) && buffer[checked_index-1]=='\r'){
				 buffer[checked_index-1]='\0';
				 buffer[checked_index++]='\0';
				 return LINE_OK;
			 }
		    return LINE_BAD;
		 }

	 }
    return LINE_OPEN;
}

/*分析请求行*/
HTTP_CODE parse_requestline(char* temp,CHECK_STATE& checkstate){
	char* url=strpbrk(temp,"\t");
	if(!url){
		return BAD_REQUEST;
	}

	*url++='\0';

	char* method=temp;
	if(strcasecmp(method,"GET")==0){
		printf("The request method is GET\n");
	}
	else{
		return BAD_REQUEST;
	}

	url+=strspn(url,"\t");
    
}

