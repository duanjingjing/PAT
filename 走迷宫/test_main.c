/*************************************************************************
	> File Name: test_main.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 25 Aug 2014 02:00:47 AM PDT
 ************************************************************************/

#include "find_path.h"

int main(){
	pNode MyStack;
	int x,y;
	int maze[ROW+2][COL+2]={
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,0,1,0,1,0,0,1,
		1,0,0,0,1,0,1,0,0,0,0,1,
		1,0,1,0,1,0,1,0,1,1,0,1,
		1,0,1,0,1,0,1,0,1,0,0,1,
		1,0,1,1,1,0,1,0,1,0,1,1,
		1,0,1,0,0,0,1,0,1,0,1,1,
		1,0,1,0,1,1,1,0,1,0,0,1,
		1,1,0,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,1,1,1,1,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1
	};

	for(x=1;x<=ROW;x++){
		for(y=1;y<=COL;y++){
			printf("%d ",maze[x][y]);
		}
		printf("\n");
	}

	stack_init(&MyStack);
	if(find_path(maze,&MyStack)){
		stack_reverse(&MyStack);
		stack_show(MyStack);
	}
	else{
		printf("No Path\n");
	}
	return 0;
}
