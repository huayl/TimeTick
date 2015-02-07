/*************************************************
* 名称：libtq.h
* 功能：头文件
* 返回：    
* 备注：库文件
***************************************************/

#ifndef _LIBTQUEUE_H
#define _LIBTQUEUE_H

#include <sys/time.h>
#include <time.h>

/* 函数声明 */
typedef void *(*run_func) (int , void *);  
typedef void *(*copy_func) (void *);
typedef void *(*free_func) (void *);
typedef int   (*cmp_func) (void *, void *);
typedef long (*tq_cmp_func) (const struct timeval *, const struct timeval *);


/* 基本结构 */
typedef struct tq_entry_info
{
    void *item;                    /* stored element (content) */
    struct tq_entry_info *next;    /* link to next entry */
    struct tq_entry_info *prev;    /* link to previous entry */
    struct timeval tv;             /* struct timeval */
    
    int has_func ; 
    
}tq_entry;


/* 双链表结构 */
typedef struct tq_info
{
	tq_entry *head;  		    /* link to beginning of tq */
	tq_entry *tail;  		    /* link to end of tq       */

	cmp_func  cmp_fn;  	        /* comparison method  */
	copy_func copy_fn; 		    /* copy method */
	free_func free_fn; 	        /* item destructor */
	run_func  func;             /* run func */ 
	tq_cmp_func  tv_cmp;        /* time comparison function */

	long items;               	/* number of elements in tq */
    int  run_all;               /* all run flag */
	int  mode;                 	/* operation mode */
    long run_num ; 
	
} tq;

/* 控制函数返回结构 */
typedef struct tq_ret_func_info
{
    void *(*ret)(int, void *);
    
}tq_ret_func;

/*************************************************
* 名称：tq_create_nosync
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
tq *tq_create(run_func run_fn, tq_cmp_func tv_cmp);



/*************************************************
* 名称：tq_destroy
* 功能：销毁链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void tq_destroy(tq *tq);


/*************************************************
* 名称：tq_item_count
* 功能：链表树目
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long tq_item_count(tq *tq);

/*************************************************
* 名称：tq_item_count
* 功能：链表插入
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_insert(tq *tq, void *item, const struct timeval *tv);


/*************************************************
* 名称：tq_item_count
* 功能：链表查找
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_search(tq *tq, void *item);

/*************************************************
* 名称：tq_item_count
* 功能：链表头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get_head(tq *tq);

/*************************************************
* 名称：tq_get
* 功能：链表值
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get(tq *tq, int num);

/*************************************************
* 名称：tq_get_tail
* 功能：链表尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get_tail(tq *tq);

/*************************************************
* 名称：tq_remove_head
* 功能：链表移除头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_remove_head(tq *tq);

/*************************************************
* 名称：tq_remove_tail
* 功能：链表移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_remove_tail(tq *tq);

/*************************************************
* 名称：tq_remove_tail
* 功能：链表空
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int  tq_is_empty(tq *tq);

/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
unsigned int tq_run(tq *tq, const struct timeval *tv);


/*************************************************
* 名称：tq_remove_all
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
unsigned int tq_run_all(tq *tq);


/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_secs(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_mins(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_hours(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_days(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long time_cmp(const struct timeval *st1, const struct timeval *st2);


/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
const struct timeval *tq_timeval(tq *t);


/*************************************************
* 名称：tdiff_usecs()
* 功能：时间比较函数
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long tdiff_usecs(const struct timeval *tv1, const struct timeval *tv2);

/*************************************************  
* 名称：tdiff_msecs()                               
* 功能：时间比较函数                                
* 返回：                                            
* 备注：库文件                                      
* 说明：                                            
***************************************************/
long tdiff_msecs(const struct timeval *tv1, const struct timeval *tv2);

 /*************************************************  
* 名称：tdiff_secs()                               
* 功能：时间比较函数                                
* 返回：                                            
* 备注：库文件                                      
* 说明：                                            
***************************************************/
long tdiff_secs(const struct timeval *tv1, const struct timeval *tv2);


#endif
