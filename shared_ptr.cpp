/*************************************************************************
	> File Name: shared_ptr.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 08 Aug 2014 05:51:23 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

template <class T>
class shared_ptr{
private:
	T* m_ptr;//被封装的指针
	unsigned int shared_count;//引用计数
public:
	shared_ptr(T *p):m_ptr(p),shared_count(1){}
	~shared_ptr(){deconstruct();}

	void deconstruct(){
		if(shared_count==1){//引用计数为1表示只有一个对象使用指针指向的内存块
           delete m_ptr;
		   m_ptr=0;
		}
		shared_count--;
	}

	T& operator*(){return *m_ptr;}
	T* operator->() {return m_ptr;}

	//复制构造函数
	shared_ptr(shared_ptr &sp):m_ptr(sp.m_ptr),shared_count(sp.shared_count){
		shared_count++;
	}

	//重载运算符
	shared_ptr& operator=(shared_ptr& sp){
		sp.shared_count++;
		deconstruct();
		m_ptr=sp.m_ptr;
		shared_count=sp.shared_count;
		return *this;
	}
};

struct Arwen{
	int age;
	Arwen(int gg):age(gg){}
};

int main(){
	
	shared_ptr<Arwen> myPtr(new Arwen(24));
    int num=myPtr->age;
   
	shared_ptr<Arwen> ptrOne(myPtr);
	num=myPtr->age;
	num=ptrOne->age;

	shared_ptr<Arwen> ptrTwo=ptrOne;
	num=ptrOne->age;
	num=ptrTwo->age;


	return 0;
}
