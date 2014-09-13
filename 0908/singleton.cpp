/*************************************************************************
	> File Name: singleton.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 08:25:49 AM PDT
 ************************************************************************/

#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;


class Singleton{
public:
	static Singleton* getInstance(){
		pthread_once(&once_,&initInstance);
		return pInstance_;
	}

	static void initInstance(){
		//注册销毁函数
		::atexit(&destroyInstance);
		pthread_=new Singleton;
	}

	static void destroyInstance(){
		cout<<"destroy"<<endl;
		delete pInstance_;
	}

private:
	Singleton(){}
	~Singleton(const Singleton&);
	void operator=(const Singleton&);
	static Singleton* pInstance_;
    static pthread_once_t once_;
};


Singleton* Singleton::pInstance_=NULL;
pthread_once_t Singleton::once_=PTHREAD_ONCE_INIT;

int main(int argc,const char* argv[]){
	Singleton* p1,*p2;
	p1=Singleton::getInstance();
	p2=Singleton::getInstance();

	cout<<p1<<endl<<p2<<endl;
}
