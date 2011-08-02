#include "list.h"
#define DEBUG
#include <stdio.h>
#include <stdlib.h>

int print_node(PNODE_T tp)
{
    printf("age=%d\t\n", tp->age);  
}

int trav_list(PNODE_T head)
{
    #ifdef DEBUG
    printf("list ...\n");
    #endif
    while(head) 
    {
        print_node(head);
        head = head->next;
    }
}

PNODE_T insert_list(PNODE_T head, PNODE_T mp)
{
    #ifdef DEBUG
    printf("insert ...\n");
    #endif
    if(!head) 
    {
       head = mp; 
       head->next = NULL;
    }
    else
    {
        mp->next = head;
        head = mp;
    }
    return head;
}

PNODE_T find_list(PNODE_T head ,int age)
{
    #ifdef DEBUG
    printf("find ...\n");
    #endif
    while(head) 
    {
        if(head->age == age)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
    
}

PNODE_T delete_list(PNODE_T head, PNODE_T dp)
{
    #ifdef DEBUG
    printf("delete ...\n");
    #endif
    PNODE_T tp; 
    if(!head)
    {
       return NULL;
    }
    else if(head == dp) 
    {
        tp = head;
        head = head->next;
        free(tp); 
        return head;
    }   

    tp = head;
    while(tp->next) 
    {
       if(tp->next == dp) 
       {
          tp->next = dp->next;
          free(dp); 
          return head;
       }
    }
    return NULL;
}

