#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Call functions
 * */
void linked_list (void)
{
        struct Linked_List_Node *head = NULL;
        struct Linked_List_Node *second = NULL;
        struct Linked_List_Node *third = NULL;

        head = (struct Linked_List_Node *) malloc (sizeof (struct Linked_List_Node));
        second = (struct Linked_List_Node *) malloc (sizeof (struct Linked_List_Node));
        third = (struct Linked_List_Node *) malloc (sizeof (struct Linked_List_Node));

        head->data = 100;
        head->next = second;

        second->data = 200;
        second->next = third;

        third->data = 300;
        third->next = NULL;

        print_list (head);
}

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