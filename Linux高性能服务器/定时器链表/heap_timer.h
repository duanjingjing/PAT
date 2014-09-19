/*************************************************************************
	> File Name: heap_timer.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 16 Sep 2014 02:23:19 AM PDT
 ************************************************************************/

#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>
#include <netinet/in.h>
#include <time.h>
using std::exception;

#define BUFFER_SIZE 64

class heap_timer; //前向声明

/*绑定socket和定时器*/
struct client_data{
	struct sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	head_timer* timer;
};

/*定时器类*/

class heap_timer{
public:
	heap_timer(int delay){
		expire=time(NULL)+delay;
	}

public:
	time_t expire;//定时器生效的绝对时间
	void (*cb_func)(client_data*);//定时器的回调函数
	client_data* user_data;//用户数据
};

/*时间堆类*/

class time_heap{
public:
	//构造函数之一,初始化一个为cap的空堆
	time_heap(int cap) throw (std::exception):capacity(cap),cur_size(0){
		array=new heap_timer* [capacity];//创建堆数组
		if(!array){
			throw std::exception();
		}

		for(int i=0;i<capacity;i++){
			array[i]=NULL;
		}
	}

	//构造函数之二,用已有数组来初始化堆
	time_heap(heap_timer** init_array,int size,int capacity)
			throw (std::exception):cur_size(size),capacity(capacity){
		if(capacity<size){
				throw std::exception();
		}
    
		if(!array){
			throw std::exception();
		}

		for(int i=0;i<capacity;i++){
			array[i]=NULL;
		}

		if(size!=0){
			/*初始化堆数组*/
			for(int i=0;i<size;i++){
				array[i]=init_array[i];
			}

			for(int i=(cur_size-1)/2;i)
		}

        
	}
};
