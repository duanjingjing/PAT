/*************************************************************************
	> File Name: find_path.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 25 Aug 2014 01:40:34 AM PDT
 ************************************************************************/

#include "find_path.h"

static int find_next_dir(Pos pre,Pos cur){
	int x_delt,y_delt;
	x_delt=cur.s_x-pre.s_x;
	y_delt=cur.s_y-pre.s_y;

	if(x_delt==0 && y_delt==1){
		return 1;
	}
	else if(x_delt==0 && y_delt==-1){
		return 3;
	}
	else if(x_delt==1 && y_delt==0){
		return 2;
	}
	else if(x_delt==-1 && y_delt==0){
		return 4;
	}
}


int find_path(int maze[][COL+2],pNode *pst){
	pNode pTop;
	Pos offset[4]={{0,1},{1,0},{0,-1},{-1,0}};//r d l u
	int dir=0;//0,1,2,3
	Pos pos_cur,pos_pre,pos_next,pos_dest;
	pos_cur.s_x=1;
	pos_cur.s_y=1;

	pos_dest.s_x=ROW;
	pos_dest.s_y=COL;

	while(pos_cur.s_x!=pos_dest.s_x || pos_cur.s_y!=pos_dest.s_y){
		stack_push(pst,pos_cur);

		maze[pos_cur.s_x][pos_cur.s_y]=1;

		while(dir!=4){
			pos_next.s_x=pos_cur.s_x+offset[dir].s_x;
			pos_next.s_y=pos_cur.s_y+offset[dir].s_y;

			if(maze[pos_next.s_x][pos_next.s_y]==0){
				break;
			}

			dir++;
		}

		if(dir==4){//no
			if(stack_empty(pst)){
				return 0;
			}
			else{
				pTop=stack_top(pst);
				pos_pre=pTop->s_ps;//pos_cur
				stack_pop(pst);
				dir=find_next_dir(pos_pre,pos_cur);
			}
		}
		else{
			pos_cur=pos_next;
			dir=0;
		}
	}

	return 1;
}

