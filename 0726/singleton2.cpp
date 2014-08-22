/*************************************************************************
	> File Name: singleton2.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 01:57:47 AM PDT
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<stdlib.h>
using namespace std;


class Singleton{
public:
	static Singleton *getInstance(){
		pthread_once(&once_,initInstance);
		return pInstance_;
	}

	static void initInstance(){
		::atexit(destroyInstance);
		pInstance_=new Singleton;
	}

	static void destroyInstance(){
		cout<<"destroy"<<endl;
		delete pInstance_;
	}
private:
	Singleton(){};
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	static Singleton *pInstance_;
	static pthread_once_t once_;
};

Singleton *Singleton::pInstance_=NULL;
pthread_once_t Singleton::once_=PTHREAD_ONCE_INIT;

int main(int argc,char *argv[]){
	Singleton *p1,*p2;
	p1=Singleton::getInstance();
	p2-Singleton::getInstance();

	cout<<p1<<endl<<p2<<endl;
	return 0;
}
