#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
 * Print any given list
 * */
void print_list (struct Linked_List_Node *n)
{
        int i = 0;
        while (n != NULL) {
                printf ("(%d) Data: %d\n", i, n->data);
                n = n->next;
                i++;
        }
}