/*************************************************************************
	> File Name: 1.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:04:06 AM PDT
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Test{
public:
	void setValue(const string& s,int a){
		s_=s;
		a_=a;
	}

	void print() const{
		cout<<s_<<" "<<a_<<endl;
	}

private:
	string s_;
	int a_;
};

int main(int argc,const char* argv[]){
	/*
	 *
	 * 函数指针的类型包含了类名
	 * 2.指向类的成员函数需要&符号
	*/
	void (Test::*func)(const string&,int)=&Test::setValue;
	void (Test::*func2)() const=&Test::print;

	Test t;
	(t.*func)("hello",12);
	(t.*func2)();
} 
