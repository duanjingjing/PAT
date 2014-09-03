/*************************************************************************
	> File Name: 2.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:14:04 AM PDT
 ************************************************************************/

#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Test{
public:
	static void draw(){
		cout<<"draw"<<endl;
	}
};

int main(int argc,const char* argv[]){
	/*
	 *1.static函数指针不含有类名
	 *2.&符号不是必要的
	 */
	void (*func)()=Test::draw;
	func();
	return 0;
}

