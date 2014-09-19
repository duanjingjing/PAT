/*************************************************************************
	> File Name: thread.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 17 Sep 2014 01:58:34 AM PDT
 ************************************************************************/

#include<stdio.h>

#include <bits/pthreadtypes.h>
#define __SIZEOF_PTHREAD_ATTR_T 36
typedef union{
	char __size[__SIZEOF_PTHREAD_ATTR_T];
	long int __align;
}pthread_attr_t;


