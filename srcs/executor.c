#include "myshell.h"

int     nodesize(t_cmd_node *cmds)
{
    t_cmd_node  *ptr;
    int         i = 0;

    ptr = cmds;
    while (ptr)
    {
        i++;
        ptr = ptr->next;
    }
    return (i);
}

void    init_exe(t_executor *exe, t_cmd_table *cmd_table)
{
    int     pipe_ptr = -1;

    if (cmd_table->infile)
        exe->in_fd = open(cmd_table->infile, O_RDONLY);
    if (!ft_strncmp(cmd_table->outfile, ">>", 2))
        exe->out_fd = open(ft_strtrim(cmd_table->outfile, "> :"), O_CREAT | O_RDWR | O_APPEND, 0644);
    else
        exe->out_fd = open(ft_strtrim(cmd_table->outfile, "> :"), O_CREAT | O_RDWR | O_TRUNC, 0644);
    exe->node_ptr = -1;
    exe->nodesize = nodesize(cmd_table->cmds);
    exe->pipe_no = 2 * (exe->nodesize - 1);
    exe->pipe = NULL;
    if (exe->pipe_no > 0)
    {
        exe->pipe = (int*)malloc(sizeof(int) * exe->pipe_no);
        while (++pipe_ptr < exe->nodesize - 1)
            pipe(exe->pipe + 2 * pipe_ptr);
    }
}

static void stop_exe(t_cmd_table *cmdt, t_executor *exe)
{
    if (exe->pid)
        kill(exe->pid, 0);
    if (cmdt->infile)
        close(exe->in_fd);
    if (cmdt->outfile)
        close(exe->out_fd);
    if (exe->pipe)
        free(exe->pipe);
}

static int  exit_executor(t_cmd_table *cmdt, t_system *myenv, t_executor *exe, int status)
{
    stop_exe(cmdt, exe);
    signal_operator(myenv, BASH_OUT);
    return (status);
}

int     executor(t_system *my_env, t_cmd_table *cmdt, t_list *cmdll)
{
    t_executor  exe;

    if (!cmdt)
        return (0);
    init_exe(&exe, cmdt);
    signal_operator(my_env, BASH_IN);
    if (is_buildins(cmdt->cmds->cmd_arr[0]))
    {
        buildins(my_env, cmdt, &exe, cmdll);
        return (exit_executor(cmdt, my_env, &exe, 1));
    }
    else if (exe.pipe_no > 1)
    {
        if (pipe_executor(my_env, cmdt, &exe) != 1)
            return (exit_executor(cmdt, my_env, &exe, 0));
    }
    else
    {
        if (single_executor(my_env, cmdt, &exe) != 1)
            return (exit_executor(cmdt, my_env, &exe, 0));
    }
    return (exit_executor(cmdt, my_env, &exe, 1));
}