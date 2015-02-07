 /*************************************************
* 名称：libtq.c
* 功能：参数获取
* 返回：    
* 备注：库文件
***************************************************/
#include <time.h>
#include <sys/time.h>
#include "libtq.h"

/*************************************************
* 名称：time_normal
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_normal(struct timeval *st)
{
   if (st->tv_usec > 1000000) 
    { 
       st->tv_sec += (st->tv_usec / 1000000); 
       st->tv_usec %= 1000000; 
   } 
}


/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_secs(struct timeval *st, unsigned long x, unsigned long y)
{

     st->tv_sec += x; 
     st->tv_usec += y; 
     
     time_normal(st);
}


/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_mins(struct timeval *st, unsigned long x, unsigned long y)
{

     st->tv_sec += (x * 60); 
     st->tv_usec += y; 
     
     time_normal(st);
}


/*************************************************
* 名称：time_add_secs
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_hours(struct timeval *st, unsigned long x, unsigned long y)
{

     st->tv_sec += (x * 60 * 60); 
     st->tv_usec += y; 
     
     time_normal(st);
}


/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void time_add_days(struct timeval *st, unsigned long x, unsigned long y)
{

     st->tv_sec += (x * 60 * 60 * 24); 
     st->tv_usec += y; 
     
     time_normal(st);
}

/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long time_cmp(const struct timeval *st1, const struct timeval *st2)
{
  return 
   (st1->tv_sec == st2->tv_sec) ? (st1->tv_usec - st2->tv_usec) : (st1->tv_sec - st2->tv_sec) ;
}

/*************************************************
* 名称：time_add_days
* 功能：
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
const struct timeval *tq_timeval(tq *t)
{ 
  tq *scan = t;
  const struct timeval *ret = NULL;
 
  
  while (scan && scan->items)
  {
    if (scan->head)
        {
            ret = &scan->head->tv;
            break;
        }    
  }
  
  return (ret);
}
