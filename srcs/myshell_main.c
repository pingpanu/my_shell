#include "myshell.h"

void    sighandler(int signal)
{
    if (signal == SIGINT) {
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
}

int main(void)
{
    char    *cmd_str = NULL;
    t_list  *cmd_ll = NULL;
    struct sigaction    act;
    struct sigaction    quit;

    //signal related function, using signal if fine
    act.sa_handler = sighandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction (SIGINT, &act, NULL);
    quit.sa_handler = SIG_IGN;
    quit.sa_flags = 0;
    sigemptyset(&quit.sa_mask);
    sigaction (SIGQUIT, &quit, NULL);
    //UI to be included here
    my_env.env_path = ft_split(getenv("PATH"), ':');
    //printf("%s\n", my_env.env_path);
    my_env.dis_str = ft_strjoin(getenv("USER"), ": ");
    while (1) 
    {
        cmd_str = readline(my_env.dis_str);
        if (cmd_str == NULL)
            break ;
        add_history(cmd_str);
        /*some function to receive cmd_str and execute it
        lexer(&cmd_ll, cmd_str);
        parser(my_env, cmd_ll);*/
        printf("%s\n", cmd_str);
        ft_lstclear(&cmd_ll);
        //free_cmdtable(&table);
    }
    printf("exit\n");
    return (0);
}