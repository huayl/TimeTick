 /*************************************************
* 名称：libctl.c
* 功能：参数获取
* 返回：    
* 备注：库文件
***************************************************/
#include "libtq.h"
#include "libcomm.h"

#define TQ_GET_FUNC 1
#define TQ_SET_FUNC 2
#define TQ_GET_FLAG_RUN_ALL 4
#define TQ_SET_FLAG_RUN_ALL 8
#define TQ_GET_COUNT_ITEMS  16



/*************************************************
* 名称：tq_control()
* 功能：队列控制函数
* 返回：    
* 备注：库文件
* 说明：

***************************************************/
static int tq_control(tq *tq, int option, ...)
{
    int ret = 0;
    
    va_list ap;
    
    va_start(ap, option);
    
    switch (option)
    {
        case TQ_GET_FUNC:
        {
             tq_ret_func *val = va_arg(ap, tq_ret_func *);
             
             val->ret = tq->func;
             ret = 1;
        }
        break;
          
        case TQ_SET_FUNC:
        {
             void *(*val)(int, void *) = va_arg(ap, run_func);
             
             tq->func = val;
             ret = 1;
        }
        break;
          
        case TQ_GET_FLAG_RUN_ALL:
        {
             int *val = va_arg(ap, int *);
             
             *val = tq->run_all;
             ret = 1;
        }
        break;
          
        case TQ_SET_FLAG_RUN_ALL:
        {
             int val = va_arg(ap, int);
             
             tq->run_all = val;
             ret = 1;
        }
        break;
        
        case TQ_GET_COUNT_ITEMS:
        {
             long *val = va_arg(ap, long *);
             
             *val = tq->items;
             ret = 1;
        }
        break;
        
        
        default:
          break;
    }
 
  va_end(ap);
 
 return ret;
}

  
/*************************************************
* 名称：tq_get_run()
* 功能：获取FLAG_RUN_ALL
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_get_run(tq *tq, int *all)
{
    int rtn;
    
    rtn = tq_control(tq, 4, all);
    
    return rtn;
}

/*************************************************
* 名称：tq_get_run()
* 功能：获取FLAG_RUN_ALL
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_set_run(tq *tq)
{
    int rtn;
    
    rtn = tq_control(tq, 8, 1);
    
    return rtn;
}

/*************************************************
* 名称：tq_get_run()
* 功能：获取FLAG_RUN_ALL
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_get_func(tq *tq, tq_ret_func func)
{
    int rtn;
    
    rtn = tq_control(tq, 1, func);
    
    return rtn;
}

/*************************************************
* 名称：tq_get_run()
* 功能：获取FLAG_RUN_ALL
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_set_func(tq *tq, run_func func)
{
    int rtn;
    
    rtn = tq_control(tq, 2, func);
    
    return rtn;
}


/*************************************************
* 名称：tq_get_run()
* 功能：获取FLAG_RUN_ALL
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_get_count(tq *tq, long *count)
{
    int rtn;
    
    rtn = tq_control(tq, 16, count);
    
    return rtn;
}

