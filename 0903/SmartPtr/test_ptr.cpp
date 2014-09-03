/*************************************************************************
	> File Name: test_ptr.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:43:02 AM PDT
 ************************************************************************/

#include "smartPtr.h"
using namespace std;

int main(int argc,const char* argv[]){
	SmartPtr ptr(new Animal);
	(*ptr).run();

	ptr->run();
	return 0;
}

