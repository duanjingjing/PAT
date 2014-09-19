/*************************************************************************
	> File Name: Lst_timer.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 15 Sep 2014 04:49:03 AM PDT
 ************************************************************************/

#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 64

class util_timer;//前向声明

/*用户数据结构:客户端socket地址、socket文件描述符、读缓存和定时器*/
struct client_data{
	struct sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	util_timer* timer;
};

/*定时器类*/
class util_timer{
public:
	util_timer():prev(NULL),next(NULL){}
public:
	time_t expire;/*任务的超时时间.这里使用绝对时间*/
	void (*cb_func)(client_data*);//任务回调函数
	client_data* user_data;
	util_timer* prev;//指向前一个定时器
	util_timer* next;//指向下一个定时器
};

/*定时器链表.它是一个升序、双向链表、且带有头结点和尾结点的链表*/
class sort_timer_lst{
public:
	sort_timer_lst():head(NULL),tail(NULL){}
	/*链表被销毁时,删除其中所有的定时器*/
	~sort_timer_lst();
	void add_timer(util_timer* timer);//将目标定时器timer添加到链表中
	void adjust_timer(util_timer* timer);//只考虑超时时间延长的情况
	void del_timer(util_timer* timer);
	void tick();//SIGALRM信号每次被触发就在其信号处理函数(如果使用统一事件源,则是主函数)
private:
	void add_timer(util_timer* timer,util_timer*lst_head);
	util_timer* head;
	util_timer* tail;
};

#endif
