/*************************************************************************
	> File Name: byteorder.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 07:37:12 AM PDT
 ************************************************************************/

#include<stdio.h>

void byteorder(){
	union{
		int value;
		char union_bytes[sizeof(int)];
	}test;

	test.value=0x01020314;
    
	/*
	if((test.union_bytes[0]==1) && (test.union_bytes[1]==2)){
		printf("big endian\n");
	}

	else if(test.union_bytes[0]==2 && (test.union_bytes[1]==1)){
		printf("little endian\n");
	}
	else{
		printf("unknown ...\n");
	}
	*/
	printf("before...:%x\n",test.value);

    int i;
	for(i=0;i<sizeof(int);i++){
		printf("%02x",test.union_bytes[i]);
	}
	printf("\n");
}

int main(int argc,const char* argv[]){
	byteorder();
}
