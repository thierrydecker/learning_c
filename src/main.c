#include <stdio.h>
#include <stdlib.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        /*
         * Print string
         * */
        printf("\nStrings format\n");
        char s[] = "Thierry DECKER";
        printf ("(%%s) -> Value of s is: %s\n", s);

        /*
         * Print numbers
         * */
        printf("\nNumbers format\n");

        /*
         * Print integers
         * */
        printf("\nIntegers format\n");
        int a = 102;
        printf ("(%%d) -> Value of a is: %d\n", a);
        printf ("(%%i) -> Value of a is: %i\n", a);

        /*
         * Print floats
         * */
        printf("\nFloats format\n");
        float f = 10200000000.125;
        printf ("(%%f) -> Value of f is: %f\n", f);
        printf ("(%%e) -> Value of f is: %e\n", f);
        printf ("(%%E) -> Value of f is: %E\n", f);
        printf ("(%%g) -> Value of f is: %g\n", f);
        printf ("(%%G) -> Value of f is: %G\n", f);

        return EXIT_SUCCESS;

}