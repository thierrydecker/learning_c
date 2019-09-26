#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        char *const arguments[] = {"nano", "/etc/network/interfaces", NULL};
        int ret;
        ret = execv ("/bin/nano", arguments);
        if (ret == -1) {
                perror ("execv");
        }
        return EXIT_SUCCESS;
}