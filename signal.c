/*This program use to try signal*/
#define _XOPEN_SOURCE  700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

struct sigaction    sa;

void    sighandler(int sig)
{
    if (sig == SIGKILL)
        exit(0);
}

int main(int argc, char **argv)
{
    char    str[20];

    memset(&sa,0,sizeof(sa));
    sa.sa_handler = &sighandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    printf("Input any string: ");
    scanf("%19s", str);
    while (1)
    {
        printf("%s\n", str);
        sleep(3);
    }
    return (0);
}