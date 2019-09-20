#include <stdlib.h>
#include <stdio.h>
#include "extvars.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
{

  /* local variable definition */
  char grade = 'B';

  switch (grade)
    {
  case 'A' :
    printf ("Excellent!\n");
      break;
  case 'B' :
  case 'C' :
    printf ("Well done\n");
      break;
  case 'D' :
    printf ("You passed\n");
      break;
  case 'F' :
    printf ("Better try again\n");
      break;
  default :
    printf ("Invalid grade\n");
    }

  printf ("Your grade is  %c\n", grade);

  return 0;
}