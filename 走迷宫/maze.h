/*************************************************************************
	> File Name: maze.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 25 Aug 2014 01:19:57 AM PDT
 ************************************************************************/

#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagpos{
	int s_x;
	int s_y;
}Pos,*pPos;

typedef struct tagnode{
	Pos s_ps;
	struct tagnode* s_next;
}Node,*pNode;


void stack_init(pNode* pst);
void stack_push(pNode* pst,Pos ps);
void stack_pop(pNode* pst);
int stack_empty(pNode* pst);
pNode stack_top(pNode* pst);

void stack_reverse(pNode* pst);
void stack_show(pNode pst);

#endif
