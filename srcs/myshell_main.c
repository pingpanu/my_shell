#include "myshell.h"

t_system    my_env; //a global variable   

void    sighandler(int signal)
{
    if (signal == SIGINT)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
}

static void     free_arr(char **arr)
{
    int     i;

    if (!arr[0])
        return ;
    i = -1;
    while (arr[++i])
        free(arr[i]);
    free(arr);
}

static void     node_clear(t_cmd_node **node)
{
    t_cmd_node  *prev;

    if (!node)
        return ;
    prev = *node;
    while(*node)
    {
        *node = (*node)->next;
        free_arr(prev->cmd_arr);
        free(prev);
        prev = *node;
    }
    *node = 0;
}

static void     free_cmdtable(t_cmd_table *cmdt)
{
    node_clear(&cmdt->cmds);
    if (cmdt->hdoc_delim)
        free(cmdt->hdoc_delim);
    if (cmdt->infile)
        free(cmdt->infile);
    if (cmdt->outfile)
        free(cmdt->outfile);
    free(cmdt);
}

static int  array_size(char **arr)
{
    int     i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

static char **copy_env(char **ev)
{
    char    **env;
    int     i;

    i = array_size(ev);
    env = ft_calloc(sizeof(char *), i + 1);
    if (!env)
        return (NULL);
    i = -1;
    while (ev[++i])
        env[i] = ft_strdup(ev[i]);
    return (env);
}

static void  init_terminal(t_system *env)
{
    tcgetattr(STDIN_FILENO, env->myshell_term);
    tcgetattr(STDIN_FILENO, env->sh_terminal);
    //env->myshell_term->c_lflag &= ~ECHOCTL;
    //env->sh_terminal->c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, env->myshell_term);
}

void     exit_shell(t_system *env, t_cmd_table *cmdt, t_list *cmdll)
{
    if (cmdt)
        free_cmdtable(cmdt);
    if (cmdll)
        ft_lstclear(&cmdll, &free_token);
    if (!env->env_path[0])
        return ;
    if (env->dis_str)
        free(env->dis_str);
    free_arr(env->env_path);
    rl_clear_history();
    printf("exit\n");
}      

int main(int ac, char **av, char **ev)
{
    char        *cmd_str = NULL;
    t_cmd_table *cmd_table;
    t_list      *cmd_ll = NULL;

    if (ac != 1 || av[1]) {
        printf("Myshell supposed to run without args\n");
        return (1);
    }
    //UI to be included here
    my_env.env_path = copy_env(ev);
    my_env.env_path = ft_split(getenv("PATH"), ':');
    my_env.dis_str = ft_strjoin(getenv("USER"), "@Myshell: ");
    my_env.act.sa_handler = sighandler;
    my_env.act.sa_flags = 0;
    sigemptyset(&my_env.act.sa_mask);
    sigaction (SIGINT, &my_env.act, NULL);
    my_env.quit.sa_handler = SIG_IGN;
    my_env.quit.sa_flags = 0;
    sigemptyset(&my_env.quit.sa_mask);
    sigaction (SIGQUIT, &my_env.quit, NULL);
    init_terminal(&my_env);
    while (1) 
    {
        cmd_str = readline(my_env.dis_str);
        if (cmd_str == NULL)
            break ;
        add_history(cmd_str);
        lexer(&cmd_ll, cmd_str);
        cmd_table = parser(cmd_ll);
        if (!executor(my_env, cmd_table))
            break ;
        free_cmdtable(cmd_table);
        printf("cmd_table cleared\n");
        ft_lstclear(&cmd_ll, &free_token);
        printf("cmd_ll cleared\n");
    }
    exit_shell(&my_env, NULL, NULL);
    return (0);
}