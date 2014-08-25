/*************************************************************************
	> File Name: maze.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 25 Aug 2014 01:22:38 AM PDT
 ************************************************************************/

#include"maze.h"

void stack_init(pNode* pst){
	*pst=NULL;
}

void stack_push(pNode* pst,Pos ps){
	pNode tmp=(pNode)calloc(1,sizeof(Node));
	tmp->s_ps=ps;
	tmp->s_next=*pst;
	*pst=tmp;
}

void stack_pop(pNode* pst){
	pNode tmp;
	if(*pst==NULL){
		return;
	}
	else{
		tmp=*pst;
		*pst=(*pst)->s_next;
		free(tmp);
	}
}

int stack_empty(pNode* pst){
	return *pst==NULL;
}

void stack_reverse(pNode* pst){
	 pNode pCur,pNext,pPre;
	 pPre=NULL;

	 if(*pst==NULL){
		 return;
	 }

	 pCur=*pst;
	 if(pCur->s_next==NULL){
		 return;
	 }
     
	 pNext=pCur->s_next;
	 while(pNext){
		 pCur->s_next=pPre;
		 pPre=pCur;
		 pCur=pNext;
		 pNext=pNext->s_next;
	 }

	 pCur->s_next=pPre;
	 *pst=pCur;
}

pNode stack_top(pNode* pst){
	if(*pst==NULL){
		return NULL;
	}
	else{
		return *pst;
	}
}

void stack_show(pNode pst){
	int x=0;
	printf("\n");

	while(pst){
		x++;
		printf("(%d,%d)",(pst->s_ps).s_x,(pst->s_ps).s_y);
		pst=pst->s_next;
		if(x%10==0){
			printf("\n");
		}
	}
	printf("\n");
}
