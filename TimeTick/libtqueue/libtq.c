 /*************************************************
* 名称：libq.c
* 功能：双向链表
* 返回：    
* 备注：库文件
***************************************************/
#include "libtq.h"
#include "libcomm.h"

#define TYPE_COPY                              1
#define TYPE_VALUES                            2
#define TYPE_DEEP                              4


/*************************************************
* 名称：ist_create_internal
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq *tq_create_internal(int mode, cmp_func cmp_fn, copy_func copy_fn,free_func item_free, run_func run_fn, tq_cmp_func tv_cmp);

/*************************************************
* 名称：tq_destroy_internal
* 功能：销毁链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void tq_destroy_internal(tq *tq, free_func fn, int mode);


/*************************************************
* 名称：tq_item_count
* 功能：链表树目
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry **tq_get_entry_ref(tq *tq, void *item);



/*************************************************
* 名称：tq_item_count
* 功能：链表插入前操作
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void *tq_insert_before(tq *tq, void *item, const struct timeval *tv, void *existing);



/*************************************************
* 名称：tq_item_count
* 功能：链表出入后操作
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void *tq_insert_after(tq *tq, void *item, const struct timeval *tv,  void *existing);

/*************************************************
* 名称：tq_create_entry
* 功能：使用共享内存模式
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_create_entry(tq *tq, void *item, const struct timeval *tv);

/*************************************************
* 名称：tq_insert_internal
* 功能：插入
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_insert_internal(tq *tq, void *item, const struct timeval *tv);

/*************************************************
* 名称：tq_insert_internal
* 功能：清除
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_internal(tq *tq, tq_entry *entry);


/*************************************************
* 名称：tq_remove_head_internal
* 功能：移除头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_head_internal(tq *tq);


/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_tail_internal(tq *tq);

/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static int tq_run_internal(tq *tq, const struct timeval *tv, int flag);


/*************************************************
* 名称：ist_create_internal
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq *tq_create_internal(int mode, cmp_func cmp_fn, copy_func copy_fn,free_func item_free, run_func run_fn, tq_cmp_func tv_cmp)
{
    tq *tq = NULL;
    
    tq = calloc(1, sizeof(struct tq_info));
    
    if (tq == NULL) 
	{
        errno = -1;
        return NULL;
    }

    tq->head       = NULL;
    tq->tail       = NULL;
    tq->cmp_fn     = cmp_fn;
    tq->copy_fn    = copy_fn;
	tq->free_fn	   = item_free;
    tq->mode       = mode;
    tq->items      = 0;
    tq->func       = run_fn;
    tq->tv_cmp     = tv_cmp;
    tq->run_all    = 0;
    tq->run_num    = 0;


    return tq;
}


/*************************************************
* 名称：tq_create_nosync
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
tq *tq_create(run_func run_fn, tq_cmp_func tv_cmp)
{
	return 
		tq_create_internal(TYPE_DEEP, (cmp_func )strcmp, NULL, (free_func)free, run_fn, tv_cmp);
}

/*************************************************
* 名称：tq_create_nosync
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
tq *tq_create_custom(run_func run_fn, free_func item_free, tq_cmp_func tv_cmp)
{
	return 
		tq_create_internal(TYPE_DEEP, (cmp_func )strcmp, NULL, item_free, run_fn, tv_cmp);
}

/*************************************************
* 名称：tq_create_nosync
* 功能：创建链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
tq *tq_create_option(int mode, cmp_func cmp_fn, copy_func copy_fn,free_func item_free, run_func run_fn, tq_cmp_func tv_cmp)
{
	return 
		tq_create_internal(mode, cmp_fn, copy_fn, item_free, run_fn, tv_cmp);
}

/*************************************************
* 名称：tq_destroy_internal
* 功能：销毁链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void tq_destroy_internal(tq *tq, free_func fn, int mode)
{
    tq_entry *curr, *next;
			
    curr = tq->head;
    while (curr) 
	{
        next = curr->next;
        if ((mode & TYPE_DEEP) && fn)
			(*fn)(curr->item);

		free(curr);
        curr = next;
    }

    free(tq);
}


/*************************************************
* 名称：tq_destroy
* 功能：销毁链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void tq_destroy(tq *tq)
{
    tq_destroy_internal(tq, tq->free_fn, tq->mode | TYPE_DEEP);
}

/*************************************************
* 名称：tq_destroy
* 功能：销毁链表
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void tq_destroy_custom(tq *tq, free_func fn)
{
    tq_destroy_internal(tq, fn, tq->mode | TYPE_DEEP);
}

/*************************************************
* 名称：tq_item_count
* 功能：链表树目
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
long tq_item_count(tq *tq)
{
    return (tq == NULL) ? 0 : tq->items;
}

/*************************************************
* 名称：tq_item_count
* 功能：链表树目
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry **tq_get_entry_ref(tq *tq, void *item)
{
    tq_entry **here = &tq->head;

    while (*here != NULL && (*tq->cmp_fn)(item, (*here)->item)) 
        here = &(*here)-> next;

    return here;
}


/*************************************************
* 名称：tq_item_count
* 功能：链表插入
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_insert(tq *tq, void *item, const struct timeval *tv)
{
    tq_entry *entry, **lookup;
    void *res = NULL;
    tq_entry **here = &tq->head;


    entry = NULL;
    if (!(tq->mode & TYPE_VALUES )) 
	{
	    
        lookup = tq_get_entry_ref(tq, item);
        if (lookup) 
            entry = *lookup;
    }
    
    if (!*here)
    { 
        entry = tq_insert_internal(tq, item, tv);
        if (entry) 
            res = entry->item;
        
        return res;
    }
        
    while (*here) 
    {
        if(((tq->tv_cmp)(tv, &(*here)->tv)) <= 0)
            {
                res = tq_insert_before(tq, item, tv, (*here)->item);
                break;
            }
            
            
        if((*here)-> next)
            here = &(*here)-> next;
        else
            {
                res = tq_insert_after(tq, item, tv, (*here)->item);
                break;
            }
    }
        

    
    return res;
}
 
/*************************************************
* 名称：tq_item_count
* 功能：链表清除
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_remove(tq *tq, void *item)
{
    void *res = NULL;
    tq_entry *here, *curr;
	int mvalbit = tq->mode & TYPE_VALUES ;
	/* int deepbit = tq->mode & TYPE_DEEP; */

    here = tq->head;
    while (here != NULL) 
	{
        curr = here;
        here = here->next;
        if ((*tq->cmp_fn)(item, curr->item) == 0) 
		{
            tq_remove_internal(tq, curr);
            
             /* error when free item, because unmalloced */
            /*
            if (deepbit && tq->free_fn) 
                (*tq->free_fn)(curr->item);
            */
              
	        free(curr);
    
            if (!mvalbit)
                break;
        }
    }

    return res;
}


/*************************************************
* 名称：tq_item_count
* 功能：链表出入后操作
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void *tq_insert_after(tq *tq, void *item, const struct timeval *tv,  void *existing)
{
    tq_entry **here, *entry;


    if (!(tq->mode) & TYPE_VALUES ) 
	{
        here = tq_get_entry_ref(tq, item);
        if (*here != NULL) 
		{
            return (*here)->item;
        }
    }

    entry = tq_create_entry(tq, item, tv);
    if (entry == NULL) 
	{
        return NULL;
    }

    here = tq_get_entry_ref(tq, existing);

    if (*here == NULL) /* no match - append to end of tq */
		here = &tq->tail;

	entry->prev = *here;
	entry->next = (*here)->next;
   	(*here)->next = entry;

	if (entry->next) 
		entry->next->prev = entry;
	else
		tq->tail = entry;
    
    tq->items++;
    

    return entry->item;
}

/*************************************************
* 名称：tq_item_count
* 功能：链表插入前操作
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static void *tq_insert_before(tq *tq, void *item, const struct timeval *tv, void *existing)
{
    tq_entry **here, *entry;
            
    if (!(tq->mode) & TYPE_VALUES ) 
	{
        here = tq_get_entry_ref(tq, item);
        if (*here != NULL) 
		{
            return (*here)->item;
        }
    }

    entry = tq_create_entry(tq, item, tv);
    if (entry == NULL) 
	{
        return NULL;
    }

    here = tq_get_entry_ref(tq, existing);

    if (*here == NULL) /* no match - insert at top of tq */
		here = &tq->head;
	
	entry->next = *here;
	entry->prev = (*here)->prev;
	(*here)->prev = entry;
	if (entry->prev)
		entry->prev->next = entry;
	else
		tq->head = entry;

    tq->items++;
        

    return entry->item;
}

/*************************************************
* 名称：tq_item_count
* 功能：链表查找
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_search(tq *tq, void *item)
{
    tq_entry **here;
    void *res;

    here = tq_get_entry_ref(tq, item);
    res = *here ? (*here)->item : NULL;

    
    return res;
}



/*************************************************
* 名称：tq_item_count
* 功能：链表头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get_head(tq *tq)
{
    void *item = NULL;
        
    if (tq->head) 
        item = tq->head->item;

    return item;
}

/*************************************************
* 名称：tq_get
* 功能：链表值
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get(tq *tq, int num)
{
    void *item = NULL;
    tq_entry *curr, *next;
    int i;
		
    curr = tq->head;
        
    for(i = 0; i<= num; i++)
	{
        next = curr->next;
        item = curr->item;
        curr = next;
    }

    return item;
}

/*************************************************
* 名称：tq_get_tail
* 功能：链表尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_get_tail(tq *tq)
{
    void *item = NULL;
        
    if (tq->tail) 
        item = tq->tail->item;

    return item;
}

/*************************************************
* 名称：tq_remove_head
* 功能：链表移除头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_remove_head(tq *tq)
{
    tq_entry *old_head;
    void *res = NULL;
   
    old_head = tq_remove_head_internal(tq);
    if (old_head) 
	{
        res = old_head->item;
        
        /* error when free item, because unmalloced */
        /*
		if ((tq->mode & TYPE_DEEP) && tq->free_fn)
			(*tq->free_fn)(old_head->item);
	   */

	    free(old_head);
    }

    return res;
}
/*************************************************
* 名称：tq_remove_tail
* 功能：链表移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
void *tq_remove_tail(tq *tq)
{
    tq_entry *old_tail;
    void *res = NULL;

    old_tail = tq_remove_tail_internal(tq);
    if (old_tail) 
	{
        res = old_tail->item;

	    free(old_tail);
    }

    return res;
}

/*************************************************
* 名称：tq_remove_tail
* 功能：链表空
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int  tq_is_empty(tq *tq)
{
    if(tq->head != NULL)
        return 1;

    return 0;
}

/*************************************************
* 名称：tq_remove_tail
* 功能：获取模式
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_get_mode(tq *tq)
{
    return tq->mode;
}

/*************************************************
* 名称：tq_set_mode
* 功能：设置模式
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_set_mode(tq *tq, int mode)
{
	
	tq->mode |= mode;


	return 0;
}

/*************************************************
* 名称：tq_set_mode
* 功能：取消设置模式
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
int tq_unset_mode(tq *tq, int mode)
{
	/* unset specified bits */
    tq->mode &= tq->mode ^ mode;
    
	return 0;
}

/*************************************************
* 名称：tq_create_entry
* 功能：使用共享内存模式
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_create_entry(tq *tq, void *item, const struct timeval *tv)
{
    tq_entry *entry;
	
    entry = (tq_entry *) calloc(1, sizeof(tq_entry));

    if (entry == NULL) 
	{
        errno = -1;
        return NULL;
    }
    
    entry->item = (tq->mode & TYPE_COPY) ? (*tq->copy_fn)(item) : item;  
    entry->tv = *tv;
    
    if(tq->func)
        entry->has_func = 1 ;
    else
        entry->has_func = 0 ;

    return entry;
}

/*************************************************
* 名称：tq_insert_internal
* 功能：插入
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_insert_internal(tq *tq, void *item, const struct timeval *tv)
{
    tq_entry *entry;

    entry = tq_create_entry(tq, item, tv);
    if (entry == NULL) 
        return NULL;
    

    entry->next = tq->head;
    tq->head = entry;
    if (entry->next)
         entry->next->prev = entry;
    if (tq->tail == NULL)
         tq->tail = entry;

    tq->items++;
   

    return entry;
}

/*************************************************
* 名称：tq_insert_internal
* 功能：清除
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_internal(tq *tq, tq_entry *entry)
{
    if (entry->prev) 
		entry->prev->next = entry->next;
    else
		tq->head = entry->next;

    if (entry->next)
		entry->next->prev = entry->prev;
    else
		tq->tail = entry->prev;

    tq->items--;

    return entry;
}


/*************************************************
* 名称：tq_remove_head_internal
* 功能：移除头
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_head_internal(tq *tq)
{
    tq_entry *old_head;

    old_head = tq->head;
    if (old_head) 
	{
        tq->head = tq->head->next;

        if (tq->head == NULL) 
			tq->tail = NULL;
        else
			tq->head->prev = NULL;

        tq->items--;
    }

    return old_head;
}

/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static tq_entry *tq_remove_tail_internal(tq *tq)
{
    tq_entry *old_tail;

    old_tail = tq->tail;
    if (old_tail) 
	{
        tq->tail = tq->tail->prev;

        if (tq->tail == NULL) 
			tq->head = NULL;
        else
			tq->tail->next = NULL;

        tq->items--;
    }

    return old_tail;
}


/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
static int tq_run_internal(tq *tq, const struct timeval *tv, int flag)
{
    unsigned int called = 0;
    void *data = NULL;
    
    tq_entry *scan = tq->head;  
    tq_entry *entry = NULL; 
    
    if((flag == 0) || (tq->run_all == 1))
    {
        while(scan)
        {
            entry = scan -> next;
  
            if (scan->has_func)
                (*tq->func)(0, scan->item);
                
            tq->run_num++;
            called++;
            
            data = tq_remove_head(tq); 
           
            scan = entry;            
        }        
        
     }
     else
     {
        while ((scan != NULL) && (((tq->tv_cmp)(&scan->tv, tv)) <= 0))
        {   
            entry = scan->next;

            if (scan->has_func)
                (*tq->func)(0, scan->item);
                
            tq->run_num++;
            called++;
            
            data = tq_remove_head(tq); 
            
            scan = entry;    
         }
        
     }

    return called;
}



/*************************************************
* 名称：tq_remove_tail_internal
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
unsigned int tq_run(tq *tq, const struct timeval *tv)
{
    return 
        tq_run_internal(tq, tv, 1);
}


/*************************************************
* 名称：tq_remove_all
* 功能：移除尾
* 返回：    
* 备注：库文件
* 说明：
***************************************************/
unsigned int tq_run_all(tq *tq)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    if(tq->run_all == 0)
         tq->run_all = 1;
    
    return 
        tq_run_internal(tq, &tv, 0);
}


