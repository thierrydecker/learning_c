#include <stdlib.h>

#include "linked_list.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
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

        return EXIT_SUCCESS;

}