/*************************************************************************
	> File Name: msg.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 03:42:12 AM PDT
 ************************************************************************/

#ifndef MSG_H_
#define MSG_H_


#define MSG_LEN 4
#define MSG_SIZE 8188

typedef struct tag{
	int s_len;
	char s_buf[MSG_SIZE];
}MSG;

#endif
