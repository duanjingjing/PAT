/*************************************************************************
	> File Name: 1.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 12:30:34 AM PDT
 ************************************************************************/

#include<stdio.h>

//状态独立的有限状态机
STATE_MACHINE(Package _pack){
	PackageType _type=_pack.GetType();
	switch(_type){
		case type_A:
			process_package_A(_pack);
			break;
		case type_B:
			process_package_B(_pack);
			break;
	}
}

//带状态转移的有限状态机
STATE_MACHINE(){
	State cur_State=type_A;
	while(cur_state!=type_C){
		Package _pack=getNewPackage();
		switch(cur_State){
			case type_A:
				process_package_state_A(_pack);
				cur_State=type_B;
				break;
			case type_B;
			    process_package_state_B(_pack);
                cur_State=type_C;
				break;
		}
	}
}


