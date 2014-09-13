/*************************************************************************
	> File Name: reference.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 01:45:52 AM PDT
 ************************************************************************/

#include<iostream>

class Person{
public:
	Person();
	virtual ~Person();
	...
private:
	std::string name;
	std::string address;
};

class Window{
public:
	...
	std::string name() const;//返回窗口
	virtual void display() const;
};

class WindowsWithSrcollBars:public Window{
public:
	...
	virtual void display() const;
};

//现在传进来的窗口是什么类型,w就表现出那种类型
void printNameAndDisplay(const Window& w){
	std::cout<<w.name();
	w.display();
}



