#include "myshell.h"

t_system    my_env; //a global variable   

void    sighandler(int signal)
{
    if (signal == SIGINT) {
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
}

static void     removenode(t_cmd_node *node)
{
    int     i = -1;

    while(node->cmd_arr[++i])
        free(node->cmd_arr[i]);
    free(node->cmd_arr);
    free(node);
}

static void     free_cmdtable(t_cmd_table *cmdt)
{
    t_cmd_node  *ptr;

    ptr = NULL;
    while (cmdt->cmds)
    {
        ptr = cmdt->cmds;
        cmdt->cmds = cmdt->cmds->next;
        removenode(ptr);
    }
    if (cmdt->hdoc_delim)
        free(cmdt->hdoc_delim);
    //if (cmdt->infile)
    //    free(cmdt->infile);
    //if (cmdt->outfile)
    //    free(cmdt->outfile);
    free(cmdt);
}

int main(void)
{
    char        *cmd_str = NULL;
    t_cmd_table *cmd_table;
    t_list      *cmd_ll = NULL;

    //UI to be included here
    my_env.env_path = ft_split(getenv("PATH"), ':');
    my_env.dis_str = ft_strjoin(getenv("USER"), "@Myshell: ");
    //signal related function, using signal if fine
    my_env.act.sa_handler = sighandler;
    my_env.act.sa_flags = 0;
    sigemptyset(&my_env.act.sa_mask);
    sigaction (SIGINT, &my_env.act, NULL);
    my_env.quit.sa_handler = SIG_IGN;
    my_env.quit.sa_flags = 0;
    sigemptyset(&my_env.quit.sa_mask);
    sigaction (SIGQUIT, &my_env.quit, NULL);
    while (1) 
    {
        cmd_str = readline(my_env.dis_str);
        if (cmd_str == NULL)
            break ;
        add_history(cmd_str);
        lexer(&cmd_ll, cmd_str);
        cmd_table = parser(cmd_ll);
        if (cmd_table->cmds)
            executor(my_env, cmd_table);
        ft_lstclear(cmd_ll);
        free_cmdtable(cmd_table);
    }
    rl_clear_history();
    printf("exit\n");
    return (0);
}