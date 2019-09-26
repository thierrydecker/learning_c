#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        int ret;
        ret = execl ("/bin/nano", "nano", "/etc/network/interfaces", NULL);
        if (ret == -1) {
                perror ("execl");
        }
        return EXIT_SUCCESS;
}