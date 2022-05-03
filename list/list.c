#include <stdio.h>
#include <stdlib.h>

#include "listtype.h"

#define FALSE 0
#define TRUE 1
#define LIST_MAX 5

NODE *node;
NODE *initLink()
{
    node = (NODE *)malloc(sizeof(NODE) * LIST_MAX);
    if (node == NULL)
    {
        printf("malloc fail");
        return NULL;
    }

    NODE *temp;
    for (int i = 0; i < LIST_MAX; i++)
    {
        temp = &node[i];
        temp->value = i;
        temp->next = temp + 1;
    }
    node[LIST_MAX-1].next = NULL;

    return &node[0];
}

int remove_listNode(NODE **root,int value)
{
    if(*root==NULL){
        printf("list is empty");
        return FALSE;
    }
    NODE *p,*q;
    p=*root;
    //if first node
    if(p->value==value)
    {
        *root = p->next;
        p =NULL;
        free(p);
        return TRUE;
    }
    //not first node
    q = p->next;
    while (q)
    {
       if(q->value==value)
       {
           p->next =  q->next;
           q =NULL;
           free(q);
            return TRUE;
       }
       p = q;
       q = q->next;
    }
    return FALSE;
}

NODE* find_listNode(NODE *root,int value)
{
    if(root==NULL){
        printf("list is empty,search fail.");
        return NULL;
    }
    NODE *p = root;
    while (p)
    {
        if(p->value == value)
        {
            return p;
        }
        p = p->next;
    }
    
    return NULL;
}
int list_insert(NODE *current, int value)
{  
    NODE *pre = NULL;
    NODE *newNode = NULL;
    newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("malloc failed.");
        return FALSE;
    }
    newNode->value = value;
    while (current != NULL && current->value < value)
    {
        pre = current;
        current = current->next;
    }
    pre->next = newNode;
    newNode->next = current;     
    return TRUE;
}

void print_list(NODE *current)
{
    if (current == NULL)
    {
        printf("current point is null\n");
        return;
    }
    while (current)
    {
        printf("%d\n", current->value);
        current = current->next;
    }
}

int main()
{
    NODE *root = initLink(root);

    list_insert(root,5);
    //printf("%d\n",root->value);
    remove_listNode(&root,6);
    print_list(root);
    NODE *find = find_listNode(root,6);
    if(find){
        printf("find one valus is %d \n",find->value);
    }
    return EXIT_SUCCESS;
}