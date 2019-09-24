#include <stdio.h>
#include "array.h"

/*
 * Rotation method 1 (Using temp array)
 * */
void array_rotate_method_one (int *array, int offset, int array_size)
{
        int temp[2];
        temp[0] = array[0];
        temp[1] = array[1];
        for (int i = 0; i < array_size; i++) {
                array[i] = array[i + offset];
        }
        array[array_size - 2] = temp[0];
        array[array_size - 1] = temp[1];
}

/*
 * Rotation method 2 (Left rotate elements one by one)
 * */
void array_rotate_method_two (int *array, int offset, int array_size)
{
        for (int i = 0; i < offset; i++) {
                int temp = array[0];
                for (int j = 1; j < array_size; j++) {
                        array[j - 1] = array[j];
                }
                array[array_size - 2] = array[array_size - 1];
                array[array_size - 1] = temp;
        }
}

/*
 * Print the given array
 * */
void array_print (int *array, int array_size)
{
        for (int i = 0; i < array_size; i++) {
                printf ("%d element: %d\n", i, array[i]);
        }
}

/*
 * GCD algorithm
 *
 * Original Euclid's subtraction based
 *
 * */
int gcd (int a, int b)
{
        if (a == 0 || b == 0) {
                return 0;
        } else {
                while (a != b) {
                        if (a > b) {
                                a -= b;
                        } else {
                                b -= a;
                        }
                }
                return a;
        }
}
