#include "libcomm.h"
#include "libtq.h"


#define STR(x) #x
#define XSTR(x) STR(x)

#define SHOW(x, y, z) \
 "File: " x "\n" \
 "Function: " y "\n" \
 "Line: " XSTR(z) "\n" \
 "Problem: "

#define PROBLEM(x) problem(SHOW(__FILE__, "unknown", __LINE__) x)

static tq *t = NULL;

static void problem(const char *str)
{
 int saved_errno = errno;

 fprintf(stderr, "%s", str);
 
 if (str[strlen(str) - 1] == ':')
   fprintf(stderr, " %d %s", saved_errno, strerror(saved_errno));
 fprintf(stderr, "%s", "\n");

 exit (EXIT_FAILURE);
}


static void *timer_func1(int type, void *data)
{

 fprintf(stderr, "Func1 data is -- %s -- \n", (char *)data);
  fflush(NULL);
}

static void * timer_func2(int type, void *data)
{
 fprintf(stderr, "¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á\n¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á-- %s -- \n", (char *)data);
 fprintf(stderr, "Func2 Data is -- %s -- \n", (char *)data);
 fflush(NULL);
}

int main(int argc, char *argv[])
{
    tq *q = NULL;
    struct timeval s_tv;
    struct timeval tv ;
    const struct timeval *tvm ;
    void *val, *val2;
    int  all;
    long count;
    
    gettimeofday(&s_tv, NULL);
    gettimeofday(&tv, NULL);

   
    t = tq_create((run_func)timer_func1, (tq_cmp_func)time_cmp);
    q = tq_create((run_func)timer_func1, (tq_cmp_func)time_cmp);
    
    time_add_secs(&s_tv, 2, 0);
    
    val = tq_insert(t, (char *)"data1", &s_tv);
    if(val == NULL)
        PROBLEM("Insert error!");
    
    time_add_secs(&tv, 1, 0);
    val = tq_insert(q, (char *)"qdata1-111111", &tv);
    if(val == NULL)
        PROBLEM("Insert error!");
        
    fprintf(stderr, "\n QQQQQQQQQNUM ---------[%s] -- \n", tq_get_head(q));  
    time_add_secs(&tv, 3, 5000);
    val2 = tq_insert(q, (char *)"qdata33333333333", &tv);
    if(val2 == NULL)
        PROBLEM("Insert error!");

    fprintf(stderr, "\n QQQQQQQQQNUM ---------[%s] -- \n", tq_get_head(q));  
    time_add_secs(&tv, 2, 0);
    val2 = tq_insert(q, (char *)"qdata2-11111", &s_tv);
    if(val2 == NULL)
        PROBLEM("Insert error!");
        
    fprintf(stderr, "\n QQQQQQQQQNUM ---------[%s] -- \n", tq_get_head(q));    
    time_add_secs(&tv, 4, 50000);
    val2 = tq_insert(q, (char *)"data44444444444", &tv);
    if(val2 == NULL)
        PROBLEM("Insert error!");
    
    fprintf(stderr, "\n QQQQQQQQQNUM ---------[%s] -- \n", tq_get_head(q));    
    time_add_secs(&tv, 5,0);
    val2 = tq_insert(q, (char *)"data1-UUUUUUUUUUUU", &tv);
    if(val2 == NULL)
        PROBLEM("Insert error!");
    

    fprintf(stderr, "\n QQQQQQQQQNUM ----------[%s] -- \n", tq_get_head(q));  
    if(val == NULL)
        PROBLEM("Insert error!");
        
    if(tq_get_run(q, &all))
        fprintf(stderr, "\n RUN_ALL_FLAG ----------[%d] -- \n", all); 
        
    if(tq_set_run(q))
        fprintf(stderr, "\n SET RUN_ALL_FLAG ----------[%d] -- \n", all); 
        
    if(tq_get_run(q, &all))
        fprintf(stderr, "\n RUN_ALL_FLAG ----------[%d] -- \n", all); 
        
        
    if(tq_get_count(q, &count))
        fprintf(stderr, "\n CCCCCCCCCCCCCCCC ----------[%ld] -- \n", count);    
     
    if(tq_set_func(q, timer_func2))
        fprintf(stderr, "\n FFFFFFFFFFFFFFFFFFFFFF ----------[%ld] -- \n", count);      
        
    tq_run_all(t);
          
     
    while ((tvm = tq_timeval(q)))
    {            
        long wait_period = 0;
        
        fprintf(stderr, "while --------- -- \n");
                 
        gettimeofday(&tv, NULL);
        
        /*
        wait_period = tdiff_usecs(tv, &s_tv);
        if (wait_period > 0)*/
        sleep(5);  

                 
        gettimeofday(&tv, NULL);
                 
        tq_run(q, &tv);
        
        fprintf(stderr, "Func **************** \n");
    }  
    
   if(tq_get_count(q, &count))
        fprintf(stderr, "\n COUNT  END _FLAG ----------[%ld] -- \n", count);        
    
    if(t->items > 0)
        tq_destroy(t);
        
    if(q->items > 0)
        tq_destroy(t);
    
    return 0;
}
