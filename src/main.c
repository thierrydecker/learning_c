#include <stdlib.h>
#include <stdio.h>
#include "array.h"
/*
 * Main function
 * */
int main (int argv, char *args[])
{

        int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
        int array_size = 8;
        int offset = 1;

        array_rotate_method_three (array, offset, array_size);
        array_print (array, array_size);

        return EXIT_SUCCESS;

}