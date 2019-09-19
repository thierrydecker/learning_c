#include "src/array.h"
#include <stdlib.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
  /*
   * Declare the variables
   * */
  int offset = 2;
  int array_size = 7;
  int array[7] = {1, 2, 3, 4, 5, 6, 7};
  /*
   * Rotate ith method 1
   * */
  array_rotate_method_two (array, offset, array_size);
  array_print (array, array_size);
  /*
   * Exit program
   * */
  return EXIT_SUCCESS;
}
