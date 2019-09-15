#include <stdlib.h>
#include <stdio.h>

/*
 * Declarations
 * */

void print_array (int array[], int array_size);

/*
 * Definitions
 * */

/*
 * Rotation method 1 (Using temp array)
 * */
void rotate_array_method_one (int *array, int offset, int array_size)
{

}

/*
 * Print the given array
 * */
void print_array (int *array, int array_size)
{
  for (int i = 0; i < array_size; i++)
    {
      printf ("%d element: %d\n", i, array[i]);
    }
}

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
  rotate_array_method_one (array, offset, array_size);
  print_array (array, array_size);

  /*
   * Exit program
   * */
  return EXIT_SUCCESS;

}
