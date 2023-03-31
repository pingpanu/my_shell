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

/*static void  init_terminal(t_system *env)
{
    tcgetattr(STDIN_FILENO, env->myshell_term);
    tcgetattr(STDIN_FILENO, env->sh_terminal);
    env->myshell_term->c_lflag &= ~(ECHO | ECHOE | ECHONL| ECHOK);
    env->sh_terminal->c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, env->myshell_term);
}*/

char    *curr_dir(void)
{
    char    *pwd;
    char    **pwd_arr;
    char    *ret;
    int     i = 0;

    pwd = ft_calloc(sizeof(char), 1000);
    if (!getcwd(pwd, 999))
        return (NULL);
    pwd_arr = ft_split(pwd, '/');
    free(pwd);
    if (!pwd_arr)
        return (NULL);
    while(pwd_arr[i])
        i++;
    ret = ft_strdup(pwd_arr[i - 1]);
    free_arr(pwd_arr);
    return (ret);
}

void     exit_shell(t_system *env)
{
    /*if (cmdt->cmds)
        free_cmdtable(cmdt);
    printf("cmdt freed\n");
    if (cmdll)
        ft_lstclear(&cmdll, &free_token);*/
    if (env->dis_str)
        free(env->dis_str);
    free_arr(env->env_cop);
    free_arr(env->env_path);
    printf("env freed\n");
    rl_clear_history();
    printf("exit\n");
    
}

int main(int ac, char **av, char **ev)
{
    char        *cmd_str = NULL;
    char        *buf;
    t_cmd_table *cmd_table;
    t_list      *cmd_ll = NULL;

    if (ac != 1 || av[1]) {
        printf("Myshell supposed to run without args\n");
        exit(1);
    }
    //UI to be included here
    my_env.env_cop = copy_env(ev);
    my_env.env_path = ft_split(getenv("PATH"), ':');
    printf("check1\n");
    buf = ft_strjoin("Myshell@ ", curr_dir());
    my_env.dis_str = ft_strjoin(buf, ": ");
    printf("check2\n");
    free(buf);
    if (!my_env.dis_str)
    {
        perror("Myshell\n");
        return (1);
    }
    my_env.act.sa_handler = sighandler;
    my_env.act.sa_flags = 0;
    sigemptyset(&my_env.act.sa_mask);
    sigaction (SIGINT, &my_env.act, NULL);
    my_env.quit.sa_handler = SIG_IGN;
    my_env.quit.sa_flags = 0;
    sigemptyset(&my_env.quit.sa_mask);
    sigaction (SIGQUIT, &my_env.quit, NULL);
    //init_terminal(&my_env);
    while (1)
    {
        cmd_str = readline(my_env.dis_str);
        if (cmd_str == NULL)
            break ;
        add_history(cmd_str);
        printf("history added\n");
        lexer(&cmd_ll, cmd_str);
        printf("cmd ll created\n");
        cmd_table = parser(cmd_ll);
        if (!executor(my_env, cmd_table))
            break ;
        free_cmdtable(cmd_table);
        ft_lstclear(&cmd_ll, &free_token);
    }
    exit_shell(&my_env);
    return (0);
}