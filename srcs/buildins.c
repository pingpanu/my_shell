# include "myshell.h"

int is_buildins(char *cmd)
{
    if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3) ||
        !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7) ||
        !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4) ||
        !ft_strncmp(cmd, "exit", 5))
        return (1);
    return (0);
}

int buildins(t_system *env, t_cmd_node *node, t_executor *exe)
{
    if (!ft_strncmp(node->cmd_arr[0], "echo", 5))
        return (exe_echo(exe, node));
    if (!ft_strncmp(node->cmd_arr[0], "cd", 3))
        return (change_dir);
    if (!ft_strncmp(node->cmd_arr[0], "pwd", 4))
        return (pwd);
    if (!ft_strncmp(node->cmd_arr[0], "export", 7))
        return (export);
    if (!ft_strncmp(node->cmd_arr[0], "unset", 6))
        return (unset);
    if (!ft_strncmp(node->cmd_arr[0], "env", 4))
        return (exe_env(env, node));
    if (!ft_strncmp(node->cmd_arr[0], "exit", 5))
        exit(0);
    perror("Command not found");
    return (0);
}