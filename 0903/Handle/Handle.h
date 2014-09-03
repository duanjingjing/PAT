/*************************************************************************
	> File Name: Handle.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:56:17 AM PDT
 ************************************************************************/

#ifndef HANDLE_H_
#define HANDLE_H_

class Animal;

class Handle{
public:
	Handle();
	Handle(const Animal&);
	Handle(const Handle&);
	Handle& operator=(const Handle&);
	~Handle();

	Animal* operator->();
	const Animal *operator->() const;

private:
	Animal *ptr_;
};

#endif

