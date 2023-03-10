#include "myshell.h"

/*void    sighandler(int signal)
{
    if (signal == SIGINT)
        printf("%p\n", NULL);
    else if (signal == SIGQUIT)
        return ;
    else if (signal == EOF)
        exit(0) ;
}*/

int main(void)
{
    char    *cmd_str = NULL;
    t_list  *cmd_ll = NULL;
    //struct sigaction    act;
    struct  stat buf;
    int     exist = 0;

    //signal related function
    /*ft_memset(&act, 0, sizeof(act));
    act.sa_handler = &sighandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);*/
    //UI to be included here
    my_env.env_path = ft_split(getenv("PATH"), ':');
    //printf("%s\n", my_env.env_path);
    my_env.dis_str = ft_strjoin(getenv("USER"), ": ");
    while (1) 
    {
        cmd_str = readline(my_env.dis_str);
        /*some function to receive cmd_str and execute it
        if (cmd_str != NULL) {
            lexer(&cmd_ll, cmd_str);
            parser(my_env, cmd_ll);
        }*/
        exist = lstat(cmd_str, &buf);
        printf("%d\n", exist);
    }
    return (0);
}