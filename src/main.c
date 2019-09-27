#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processes.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        pid_t forked_pid = fork ();;

        if (forked_pid > 0) {
                printf ("I am the parent!\n");
        } else if (forked_pid == 0) {
                printf ("I am the child!\n");
        } else if (forked_pid < 0) {
                perror ("fork");
                return EXIT_FAILURE;
        }
        process_print ();
        return EXIT_SUCCESS;
}