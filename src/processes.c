#include "processes.h"

#include <stdio.h>
#include <unistd.h>

/*
 * Print process related values
 * */
void process_print (void)
{
        pid_print ();
        ppid_print ();
}

/*
 * Print the Process ID
 * */
void pid_print (void)
{
        printf ("My pid is: %d\n", getpid ());
}

/*
 * Print the Parent's Process ID
 * */
void ppid_print (void)
{
        printf ("My parent's pid is: %d\n", getppid ());
}
