#include <stdlib.h>
#include <stdio.h>
#include "array.h"
/*
 * Main function
 * */
int main (int argv, char *args[])
{

        int a = 124;
        int b = 32;
        printf ("GCD of %d and %d is %d", a, b, gcd (a, b));

        return EXIT_SUCCESS;

}