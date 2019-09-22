#include "printing.h"

#include <stdio.h>

void print_me (void)
{
        /*
         * Print string
         * */
        printf ("\nStrings format\n");
        char s[] = "Thierry DECKER";
        printf ("(%%s) -> Value of s is : %s\n", s);

        /*
         * Print numbers
         * */
        printf ("\nNumbers format\n");

        /*
         * Print integers
         * */
        printf ("\nIntegers format\n");
        int a = -102;
        unsigned int b = 1254;
        printf ("(%%d) -> Value of a is : %d\n", a);
        printf ("(%%i) -> Value of a is : %i\n", a);
        printf ("(%%u) -> Value of a is : %i\n", b);

        /*
         * Print floats
         * */
        printf ("\nFloats format\n");
        double f = 102.125;
        printf ("(%%f) -> Value of f is : %f\n", f);
        printf ("(%%e) -> Value of f is : %e\n", f);
        printf ("(%%E) -> Value of f is : %E\n", f);
        printf ("(%%g) -> Value of f is : %g\n", f);
        printf ("(%%G) -> Value of f is : %G\n", f);

        /*
         * Length modifier
         * */
        long double g = 3.1415926535;
        printf ("(%%Lg) -> Value of g is: %Lg\n", g);

        /*
         * Precision modifier
         * */
        printf ("(%%.3f) -> Value of f is : %.1f\n", f);
        printf ("(%%.5d) -> Value of a is : %.5d\n", a);
        printf ("(%%.5s) -> Value of s is : %.5s\n", s);

}