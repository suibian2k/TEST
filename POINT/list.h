#ifndef _LIST_H_
#define _LIST_H_
typedef struct stu
{
    int age;
    struct stu *next;
}NODE_T, *PNODE_T;

int print_node(PNODE_T tp);
int trav_list(PNODE_T head);
PNODE_T insert_list(PNODE_T head, const PNODE_T mp);
PNODE_T find_list(PNODE_T head ,int age);
PNODE_T delete_list(PNODE_T head, PNODE_T dp);

//dd ffd df
#endif
