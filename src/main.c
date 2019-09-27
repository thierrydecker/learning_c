#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        pid_t forked_pid;
        forked_pid = fork ();
        if (forked_pid == -1) {
                perror ("fork");
                return EXIT_FAILURE;
        }
        /* the child ... */
        if (forked_pid == 0) {
                char *const arguments[] = {"cat", "/etc/network/interfaces", NULL};
                int ret;
                ret = execv ("/usr/bin/cat", arguments);
                if (ret == -1) {
                        perror ("execv");
                        return EXIT_FAILURE;
                }
        }
        return EXIT_SUCCESS;
}