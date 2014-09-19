/*************************************************************************
	> File Name: Lst_timer.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 15 Sep 2014 08:32:53 PM PDT
 ************************************************************************/

#include "Lst_timer.h"
#include <iostream>
using namespace std;

sort_timer_lst::~sort_timer_lst(){
	util_timer* tmp=head;
	while(tmp){
		head=head->next;
		delete tmp;
		tmp=head;
	}
}

/*将目标定时器timer添加到链表中*/
void sort_timer_lst::add_timer(util_timer* timer){
	 if(!timer){
		 return;
	 }

	 if(!head){
		 return;
	 }

	 if(timer->expire<head->expire){
		 timer->next=head;
		 head->prev=timer;
		 head=timer;
		 return;
	 }

	 add_timer(timer,head);
}

void sort_timer_lst::adjust_timer(util_timer* timer){
     if(!timer){
		 return;
	 }

	 util_timer* tmp=timer->next;
	 if(!tmp || (timer->expire<tmp->expire)){
		 return;
	 }

	 if(timer==head){
		 head=head->next;
		 head->prev=NULL;
		 timer->next=NULL;
		 add_timer(timer,head);
	 }

	 else{
		 timer->prev->next=timer->next;
		 timer->next->prev=timer->prev;
		 add_timer(timer,timer->next);
	 }
}

void sort_timer_lst::del_timer(util_timer* timer){
	 if(!timer){
		 return;
	 }
     
     if((timer==head) && (tail==timer)){
		 delete timer;
		 head=tail=NULL;
		 return;
	 }

	 if(timer==head){
		 head=timer->next;
		 head->prev=NULL;
		 delete timer;
		 return;
	 }

	 if(timer==tail){
		 tail=tail->prev;
		 tail->next=NULL;
		 delete timer;
		 return;
	 }

	 timer->prev->next=timer->next;
	 timer->next->prev=timer->prev;
	 delete timer;
}


void sort_timer_lst::tick(){
	if(!head){
		return;
	}

	cout<<"timer tick\n";
	time_t cur=time(NULL);
	util_timer* tmp=head;
	/*从头结点开始依次处理每个定时器,直到遇到一个尚未到期的定时器*/
	while(tmp){
		if(cur<tmp->expire){
			break;
		}

		/*调用定时器的回调函数,以执行定时任务*/
		tmp->cb_func(tmp->user_data);
		/*执行完定时器中的定时任务之后，就将其从链表中删除,并重值链表头结点*/
		head=tmp->next;
		if(head){
			head->prev=NULL;
		}

		delete tmp;
		tmp=head;
	}
}

/*一个重载的辅助函数,它被共有的add_timer和adjust_timer函数调用。该函数表示将目标定时器timer添加到lst_head之后的部分链表中*/
void sort_timer_lst::add_timer(util_timer* timer,util_timer* lst_head){
	 util_timer* prev=lst_head;
	 util_timer* tmp=prev->next;

	 while(tmp){
		 if(timer->expire<tmp->expire){
			 prev->next=timer;
			 timer->next=tmp;
			 tmp->prev=timer;
			 timer->prev=prev;
			 break;
		 }

		 prev=tmp;
		 tmp=tmp->next;
	 }

	 //如果没有找到,就插入尾结点
	 if(!tmp){
		 prev->next=timer;
		 timer->prev=prev;
		 timer->next=NULL;
		 tail=timer;
	 }
}
