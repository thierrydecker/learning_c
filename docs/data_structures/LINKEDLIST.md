# Linked list

Like arrays, a Linked List is a linear data structure. 

Unlike arrays, linked list elements are not stored at a contiguous location; the elements are linked using pointers.

![Arrays in memory](../images/Linkedlist.png)

## Why Linked List?

Arrays can be used to store linear data of similar types, but arrays have the following limitations.

- The size of the arrays is fixed: So we must know the upper limit on the number of elements in advance. Also, 
generally, the allocated memory is equal to the upper limit irrespective of the usage.

- Inserting a new element in an array of elements is expensive because the room has to be created for the new elements 
and to create room existing elements have to be shifted.

For example, in a system, if we maintain a sorted list of IDs in an array `id[]`.

`id[] = [1000, 1010, 1050, 2000, 2040].`

And if we want to insert a new ID 1005, then to maintain the sorted order, we have to move all the elements after 1000 
(excluding 1000).

Deletion is also expensive with arrays until unless some special techniques are used. For example, to delete 1010 in 
id[], everything after 1010 has to be moved.

## Advantages over arrays

- Dynamic size

- Ease of insertion/deletion

## Drawbacks

- Random access is not allowed. We have to access elements sequentially starting from the first node. So we cannot do 
binary search with linked lists efficiently with its default implementation. Read about it here.

- Extra memory space for a pointer is required with each element of the list.

- Not cache friendly. Since array elements are contiguous locations, there is locality of reference which is not there 
in case of linked lists.

## Representation

A linked list is represented by a pointer to the first node of the linked list. The first node is called the head. If 
the linked list is empty, then the value of the head is NULL.

Each node in a list consists of at least two parts:

- data

- Pointer (Or Reference) to the next node

In C, we can represent a node using structures. 

Below is an example of a linked list node with integer data.

```
struct Node {
        int data;
        struct Node *next;
}; 
```

First Simple Linked List in C Let us create a simple linked list with 3 nodes.

```
/*
 * A simple C program to introduce a linked list
 * */
#include <stdio.h>
#include <stdlib.h>

struct Node {
        int data;
        struct Node *next;
};

/*
 * Program to create a simple linked list with 3 nodes
 * */
int main ()
{
        /*
         * Declare three pointers to the Node structure type
         * and initialize them to NULL (best practice)
         * */
        struct Node *head = NULL;
        struct Node *second = NULL;
        struct Node *third = NULL;

        /*
         * allocate 3 nodes in the heap
         * */
        head = (struct Node *) malloc (sizeof (struct Node));
        second = (struct Node *) malloc (sizeof (struct Node));
        third = (struct Node *) malloc (sizeof (struct Node));

        /* Three blocks have been allocated dynamically.
         * We have pointers to these three blocks as head,
         * second and third
         * Data is random because we haven’t assigned
         * anything yet
         * */

        /*
         * Assign data in first node
         * */
        head->data = 1;

        /*
         * Link first node with the second node
         * */
        head->next = second;
        /*
         * Data has been assigned to the data part of the first
         * block (block pointed by the head). And next
         * pointer of first block points to second.
         * So they both are linked.
         * */

        /*
         * Assign data to second node
         * */
        second->data = 2;

        /*
         * Link second node with the third node
         * */
        second->next = third;

        /*
         * data has been assigned to the data part of the second
         * block (block pointed by second). And next
         * pointer of the second block points to the third
         * block. So all three blocks are linked.
         * */

        third->data = 3; // assign data to third node
        third->next = NULL;

        /*
         * data has been assigned to data part of third
         * block (block pointed by third). And next pointer
         * of the third block is made NULL to indicate
         * that the linked list is terminated here.
         *
         * Note that only head is sufficient to represent
         * the whole list. We can traverse the complete
         * list by following next pointers.
         * */

        return 0;
}
 
```