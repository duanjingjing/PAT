/*************************************************************************
	> File Name: test_main.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 02:04:35 AM PDT
 ************************************************************************/

#include "Animal.h"
#include "Handle.h"
#include <vector>
#include <iostream>
using namespace std;

int main(int argc,const char* argv[]){
	vector<Handle> vec;

	Dog d1,d2;
	Cat c;
	Bear b1,b2,b3;

	vec.push_back(d1);
	vec.push_back(d2);
	vec.push_back(c);
	vec.push_back(b1);
	vec.push_back(b2);
	vec.push_back(b3);


	for(vector<Handle>::iterator it=vec.begin();it!=vec.end();it++){
		(*it)->display();
	}

	return 0;
}

