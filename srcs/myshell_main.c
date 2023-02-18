#include "myshell.h"

void    sighandler(int signal)
{
    if (signal == SIGINT)
        cmd_str = readline(dis_str);
    else if (signal == SIGQUIT)
        return ;
    else if (signal == EOF)
        exit(0);
}

int main(void)
{
    char    *cmd_str; //should be global variable.
    char    *dis_str; //also should be global variable
    struct sigaction    act;
    
    //signal related function
    ft_memset(&act, 0, sizeof(act));
    act.sa_handler = &sighandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);
    //UI to be included here
    g_envpath = getenv("PATH");
    dis_str = ft_strjoin(getenv("USER"), ": ");
    while (1) 
    {
        cmd_str = readline(dis_str);
        //some function to receive cmd_str and execute it
    }
    return (0);
}