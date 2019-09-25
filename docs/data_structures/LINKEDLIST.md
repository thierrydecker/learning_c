# Linked list

Like arrays, a Linked List is a linear data structure. 

Unlike arrays, linked list elements are not stored at a contiguous location; the elements are linked using pointers.

![Arrays in memory](../images/Linkedlist.png)

## Why Linked List?

Arrays can be used to store linear data of similar types, but arrays have the following limitations.

1) The size of the arrays is fixed: So we must know the upper limit on the number of elements in advance. Also, 
generally, the allocated memory is equal to the upper limit irrespective of the usage.

2) Inserting a new element in an array of elements is expensive because the room has to be created for the new elements 
and to create room existing elements have to be shifted.

For example, in a system, if we maintain a sorted list of IDs in an array `id[]`.

`id[] = [1000, 1010, 1050, 2000, 2040].`

And if we want to insert a new ID 1005, then to maintain the sorted order, we have to move all the elements after 1000 
(excluding 1000).

Deletion is also expensive with arrays until unless some special techniques are used. For example, to delete 1010 in 
id[], everything after 1010 has to be moved.

