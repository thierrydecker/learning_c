#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Linked_List_Node {
        int data;
        struct Linked_List_Node *next;
};

void linked_list (void);
void print_list (struct Linked_List_Node *n);

#endif
