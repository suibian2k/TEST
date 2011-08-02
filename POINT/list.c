#include "list.h"
#include <stdio.h>

int print_node(PNODE_T tp)
{
    printf("age=%d\t\n", tp->age);  
}

int trav_list(PNODE_T head)
{
    printf("list ...\n");
    while(head) 
    {
        print_node(head);
        head = head->next;
    }
}

PNODE_T insert_list(PNODE_T head, PNODE_T mp)
{
    if(!head) 
    {
       head = mp; 
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

