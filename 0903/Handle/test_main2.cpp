/*************************************************************************
	> File Name: test_main2.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 02:19:32 AM PDT
 ************************************************************************/

#include "Handle.h"
#include "Animal.h"
#include<iostream>
using namespace std;


int main(int argc,const char* argv[]){
	Dog d;
	Handle h(d);
	h->display();
	return 0;
}
