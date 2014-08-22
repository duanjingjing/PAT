/*************************************************************************
	> File Name: def.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 02:07:16 AM PDT
 ************************************************************************/

#ifndef DEF_H_
#define DEF_H_

#define  BOOL int
#define  TRUE 1
#define  FALSE 0

typedef struct{
	void (*thread_callback)(void*);//任务执行函数
	void *arg;
}task_t;

//thread_callback(arg)执行任务
//任务队列的结点
typedef struct q_node{
	task_t data_;
	struct q_node *next_;
}q_node,*p_node;

//任务队列
typedef struct{
	p_node head_;
	p_node tail_;
	size_t size_;
}queue;

typedef struct{
	size_t size_;//线程池的大小
	pthread_t *pthreads_;//线程数组
	int is_started_;//pool是否开启
	queue task_queue_;//任务队列
	pthread_mutex_t mutex_;//互斥锁
    pthread_cond_t cond_;//条件变量，用于通知消费者取任务
}pool_t;


void queue_init(queue*);
void queue_destroy(queue*);
void queue_push(queue*,task_t);
void queue_pop(queue*);
task_t queue_top(const queue*);
BOOL queue_is_empty(const queue*);
size_t queue_get_size(const queue*);

void thread_pool_init(pool_t *,size_t size);//初始化线程池
void thread_pool_destroy(pool_t *);//销毁线程池
void thread_pool_start(pool_t *);//启动线程池
void thread_pool_stop(pool_t *);//停止
void thread_pool_add_task_to_queue(pool_t *);//添加任务
BOOL thread_pool_get_task_from_queue(pool_t *);//取任务
BOOL thread_pool_is_started(const pool_t *);//是否开启
size_t thread_pool_get_size_of_queue(const pool_t *);//任务队列的大小

#endif
