/*************************************************************************
	> File Name: smartPtr.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:36:01 AM PDT
 ************************************************************************/

#ifndef SMARTPTR
#define SMARTPTR


#include <iostream>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);\
    void operator=(const TypeName&)

class Animal{
public:
	Animal(){
		std::cout<<"construct....."<<std::endl;
	}

	~Animal(){
		std::cout<<"destruct..."<<std::endl;
	}

	void run(){
		std::cout<<"running...."<<std::endl;
	}
};

class SmartPtr{
public:
	SmartPtr(Animal *ptr);
	~SmartPtr();

	Animal &operator*();
	const Animal &operator*() const;

	Animal* operator->();
	const Animal* operator->() const;

private:
	DISALLOW_COPY_AND_ASSIGN(SmartPtr);
	Animal *ptr_;
};

#endif
