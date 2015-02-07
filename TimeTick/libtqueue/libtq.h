/*************************************************
* ���ƣ�libtq.h
* ���ܣ�ͷ�ļ�
* ���أ�    
* ��ע�����ļ�
***************************************************/

#ifndef _LIBTQUEUE_H
#define _LIBTQUEUE_H

#include <sys/time.h>
#include <time.h>

/* �������� */
typedef void *(*run_func) (int , void *);  
typedef void *(*copy_func) (void *);
typedef void *(*free_func) (void *);
typedef int   (*cmp_func) (void *, void *);
typedef long (*tq_cmp_func) (const struct timeval *, const struct timeval *);


/* �����ṹ */
typedef struct tq_entry_info
{
    void *item;                    /* stored element (content) */
    struct tq_entry_info *next;    /* link to next entry */
    struct tq_entry_info *prev;    /* link to previous entry */
    struct timeval tv;             /* struct timeval */
    
    int has_func ; 
    
}tq_entry;


/* ˫����ṹ */
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

/* ���ƺ������ؽṹ */
typedef struct tq_ret_func_info
{
    void *(*ret)(int, void *);
    
}tq_ret_func;

/*************************************************
* ���ƣ�tq_create_nosync
* ���ܣ���������
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
tq *tq_create(run_func run_fn, tq_cmp_func tv_cmp);



/*************************************************
* ���ƣ�tq_destroy
* ���ܣ���������
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void tq_destroy(tq *tq);


/*************************************************
* ���ƣ�tq_item_count
* ���ܣ�������Ŀ
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
long tq_item_count(tq *tq);

/*************************************************
* ���ƣ�tq_item_count
* ���ܣ��������
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_insert(tq *tq, void *item, const struct timeval *tv);


/*************************************************
* ���ƣ�tq_item_count
* ���ܣ��������
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_search(tq *tq, void *item);

/*************************************************
* ���ƣ�tq_item_count
* ���ܣ�����ͷ
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_get_head(tq *tq);

/*************************************************
* ���ƣ�tq_get
* ���ܣ�����ֵ
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_get(tq *tq, int num);

/*************************************************
* ���ƣ�tq_get_tail
* ���ܣ�����β
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_get_tail(tq *tq);

/*************************************************
* ���ƣ�tq_remove_head
* ���ܣ������Ƴ�ͷ
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_remove_head(tq *tq);

/*************************************************
* ���ƣ�tq_remove_tail
* ���ܣ������Ƴ�β
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void *tq_remove_tail(tq *tq);

/*************************************************
* ���ƣ�tq_remove_tail
* ���ܣ������
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
int  tq_is_empty(tq *tq);

/*************************************************
* ���ƣ�tq_remove_tail_internal
* ���ܣ��Ƴ�β
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
unsigned int tq_run(tq *tq, const struct timeval *tv);


/*************************************************
* ���ƣ�tq_remove_all
* ���ܣ��Ƴ�β
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
unsigned int tq_run_all(tq *tq);


/*************************************************
* ���ƣ�time_add_secs
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void time_add_secs(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* ���ƣ�time_add_secs
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void time_add_mins(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* ���ƣ�time_add_secs
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void time_add_hours(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* ���ƣ�time_add_days
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
void time_add_days(struct timeval *st, unsigned long x, unsigned long y);

/*************************************************
* ���ƣ�time_add_days
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
long time_cmp(const struct timeval *st1, const struct timeval *st2);


/*************************************************
* ���ƣ�time_add_days
* ���ܣ�
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
const struct timeval *tq_timeval(tq *t);


/*************************************************
* ���ƣ�tdiff_usecs()
* ���ܣ�ʱ��ȽϺ���
* ���أ�    
* ��ע�����ļ�
* ˵����
***************************************************/
long tdiff_usecs(const struct timeval *tv1, const struct timeval *tv2);

/*************************************************  
* ���ƣ�tdiff_msecs()                               
* ���ܣ�ʱ��ȽϺ���                                
* ���أ�                                            
* ��ע�����ļ�                                      
* ˵����                                            
***************************************************/
long tdiff_msecs(const struct timeval *tv1, const struct timeval *tv2);

 /*************************************************  
* ���ƣ�tdiff_secs()                               
* ���ܣ�ʱ��ȽϺ���                                
* ���أ�                                            
* ��ע�����ļ�                                      
* ˵����                                            
***************************************************/
long tdiff_secs(const struct timeval *tv1, const struct timeval *tv2);


#endif
