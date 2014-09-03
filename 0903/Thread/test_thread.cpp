/*************************************************************************
	> File Name: test_thread.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 05:10:11 AM PDT
 ************************************************************************/

#include "Thread.h"
#include<iostream>
#include <unistd.h>
using namespace std;

class TestThread:public Thread{
public:
	void run(){
		while(1){
			sleep(1);
			cout<<"hello..."<<endl;
		}
	}
};

int main(int argc,const char* argv[]){
	TestThread t;
	t.start();
	t.join();
	return 0;
}

