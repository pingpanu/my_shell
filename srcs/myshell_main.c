#include "myshell.h"

void    sighandler(int signal)
{
    if (signal == SIGINT) 
        ;
}

int main(void)
{
    char    *cmd_str = NULL;
    t_list  *cmd_ll = NULL;
    struct sigaction    act;

    //signal related function
    act.sa_handler = sighandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction (SIGINT, &act, NULL);
    sigaction (SIGTSTP, &act, NULL);
    //UI to be included here
    my_env.env_path = ft_split(getenv("PATH"), ':');
    //printf("%s\n", my_env.env_path);
    my_env.dis_str = ft_strjoin(getenv("USER"), ": ");
    while (1) 
    {
        cmd_str = readline(my_env.dis_str);
        if (!ft_strncmp(cmd_str, "", 1))
            rl_redisplay();
        /*some function to receive cmd_str and execute it
        if (cmd_str != NULL) {
            lexer(&cmd_ll, cmd_str);
            parser(my_env, cmd_ll);
        }*/
        printf("%s\n", cmd_str);
    }
    return (0);
}