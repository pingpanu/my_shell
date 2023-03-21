#include "myshell.h"

void    init_exe(t_executor *exe, t_cmd_table *cmd_table)
{
    int     pipe_ptr = -1;

    exe->node_ptr = -1;
    exe->nodesize = nodesize(cmd_table->cmds);
    exe->pipe_no = 2 * (exe->nodesize - 1);
    if (exe->pipe_no > 0)
    {
        exe->pipe = (int*)malloc(sizeof(int) * exe->pipe_no);
        while (++pipe_ptr < exe->nodesize - 1)
        {
            if (pipe(exe->pipe + 2 * pipe_ptr) < 0)
                pipe_free(exe);
        }
    }
}

int     pipe_executor(t_system env, t_cmd_table *cmdt, t_executor *exe)
{
    char        *path;
    t_cmd_node  *cmd_ptr;

    cmd_ptr = cmdt->cmds;
    while (cmd_ptr->next)
    {
        new_pipex(env, cmd_ptr->cmd_arr, cmd_ptr->next->cmd_arr, exe);
        cmd_ptr = cmd_ptr->next;
    }
    return (1);
}

int     single_executor(t_system env, t_cmd_table *cmdt, t_executor *exe)
{
    char    *path;

    dup_fd(cmdt);
    exe->pid = fork();
    if (exe->pid < 0)
        return (0);
    else if (exe->pid == 0)
    {
        path = find_path(cmdt->cmds->cmd_arr[0], env.env_path);
        if (execve(path, cmdt->cmds->cmd_arr, NULL) == -1)
            buildins(env, cmdt, exe);
    }
    else
        wait(NULL);
    return (1);
}

int     executor(t_system my_env, t_cmd_table *cmd_table)
{
    t_executor  exe;

    init_exe(&exe, cmd_table);
    signal_operator(&my_env, INPUT);
    if (exe.pipe_no > 0)
    {
        if (pipe_executor(my_env, cmd_table, &exe) < 1)
            return (0);
    }
    else
    {
        if (single_executor(my_env, cmd_table, &exe) < 1);
            return (0);
    }
    signal_operator(&my_env, OUTPUT);
    return (1);
}