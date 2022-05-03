#ifndef List_TYPE_H
#define List_TYPE_H



struct node
{
    struct node *next;
    int value;
};
typedef struct node NODE;

NODE* initLink();
extern int list_insert(NODE *root,int value);
extern void print_list(NODE *root);
extern int remove_listNode(NODE **root,int value);
extern NODE* find_listNode(NODE *root,int value);
#endif