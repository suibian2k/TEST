#include <stdio.h>
#include <stdlib.h>
#include "list.h"

PNODE_T getNode()
{
    PNODE_T mp;    
    int age;

    while(1) 
    {
        printf("enter your age:\n");
        scanf("%d", &age);
        if(age >= 0) 
        {
            break;
        }
    }

    mp = malloc(sizeof(NODE_T));
    mp->age = age;
    mp->next = NULL;
    
}
int main(int argc, const char *argv[])
{
    NODE_T *head = NULL;    
    NODE_T *mp = NULL;
    int key = 4;

    while(1) 
    {
        mp = getNode();
        head = insert_list(head, mp);
        trav_list(head);
        mp = find_list(head, key);
        if(mp) 
        {
            print_node(mp);
            head = delete_list(head, mp);
        }
        else
        {
            printf("no age %d\n", key);
        }
    }
    return 0;
    //sdf
}
