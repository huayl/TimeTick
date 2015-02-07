/*************************************************
* 名称：libpub.c
* 功能：公共处理
* 返回：    
* 备注：库文件
***************************************************/

#include "libcomm.h"
#include <limits.h>

/*************************************************
* 名称：tdiff_usecs()
* 功能：时间比较函数
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long tdiff_usecs(const struct timeval *tv1, const struct timeval *tv2)
{
    long start_sec = 0;
    long start_usec = 0;
    long end_sec = 0;
    long end_usec = 0;
    long ret = 0;
    
    if (tv1->tv_sec == tv2->tv_sec)
        return (tv1->tv_usec - tv2->tv_usec);
    else if (tv1->tv_sec > tv2->tv_sec)
    {
        start_sec = tv2->tv_sec;
        end_sec = tv1->tv_sec;
        start_usec = tv2->tv_usec;
        end_usec = tv1->tv_usec;
    }
    else
    {
        start_sec = tv1->tv_sec;
        end_sec = tv2->tv_sec;
        start_usec = tv1->tv_usec;
        end_usec = tv2->tv_usec;
    }
    
    if ((end_sec - start_sec) > ((LONG_MAX / 1000000) - 1))
    {
        if (tv1->tv_sec > tv2->tv_sec)
            return (LONG_MAX);
        return (LONG_MIN);
    }
    
    if (end_usec < start_usec)
    {
        end_usec += 1000000;
        --end_sec;
    }
    
    ret = (((end_sec - start_sec) * 1000000) + (end_usec - start_usec));
    
    if (tv1->tv_sec > tv2->tv_sec)
      return (ret);
      
    return (-ret);
}  


/*************************************************  
* 名称：tdiff_msecs()                               
* 功能：时间比较函数                                
* 返回：                                            
* 备注：库文件                                      
* 说明：                                            
***************************************************/
long tdiff_msecs(const struct timeval *tv1, const struct timeval *tv2)
{
   long start_sec = 0;
   long start_usec = 0;
   long end_sec = 0;
   long end_usec = 0;
   long ret = 0;
   
   if (tv1->tv_sec == tv2->tv_sec)
   {
       if (tv1->tv_usec <= tv2->tv_usec)
         return (0);
       return ((tv1->tv_usec - tv2->tv_usec) / 1000);
   }
   else if (tv1->tv_sec < tv2->tv_sec)
        return (0);
   
   start_sec = tv2->tv_sec;
   end_sec = tv1->tv_sec;
   start_usec = tv2->tv_usec;
   end_usec = tv1->tv_usec;
   
   if ((end_sec - start_sec) > (LONG_MAX / 1000) - 1)
       return (LONG_MAX);
   
   if (end_usec < start_usec)
   {
       end_usec += 1000000;
       --end_sec;
   }
   
   if (start_usec)
     start_usec /= 1000;
   if (end_usec)
     end_usec /= 1000;
   
   ret = (((end_sec - start_sec) * 1000) + (end_usec - start_usec));
   
   return (ret);
}


 /*************************************************  
* 名称：tdiff_secs()                               
* 功能：时间比较函数                                
* 返回：                                            
* 备注：库文件                                      
* 说明：                                            
***************************************************/
long tdiff_secs(const struct timeval *tv1, const struct timeval *tv2)
{
    long start_sec = 0;
    long start_usec = 0;
    long end_sec = 0;
    long end_usec = 0;
    long ret = 0;
    
    if (tv1->tv_sec <= tv2->tv_sec)
        return (0);
    
    start_sec = tv2->tv_sec;
    end_sec = tv1->tv_sec;
    start_usec = tv2->tv_usec;
    end_usec = tv1->tv_usec;
    
    if (end_usec < start_usec)
    {
        end_usec += 1000000;
        --end_sec;
    }
    
    if (start_usec)
        start_usec /= 1000000;
    if (end_usec)
        end_usec /= 1000000;
    
    ret = ((end_sec - start_sec) + (end_usec - start_usec));
    
    return (ret);
}




