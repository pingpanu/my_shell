#include "myshell.h"

char    *find_path(char *cmd, char **env_path)
{
    char    *proto_ret;
    char    *ret;
    int     i = -1;

    /*check if argv[1] is cmd installed in the computer*/
    while (env_path[++i])
    {
        proto_ret = ft_strjoin(env_path[i], "/");
        ret = ft_strjoin(proto_ret, cmd);
        free(proto_ret);
        if (access(ret, F_OK) == 0)
            return (ret);
        free(ret);
    }
    /*when argv[1] is not cmd installed in the computer*/
    /*check if we can access the file*/
    if (access(cmd, F_OK) == 0)
         return (cmd);
   printf("%s: No such file or directory\n", cmd);
    return (NULL);
}

int     single_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe)
{
    signal_operator(env, BASH_OPT);
    if (cmdt->infile != NULL)
    {
        if (exe->in_fd < 0) {
            perror("file not found");
            return (1);
        }
        dup2(exe->in_fd, STDIN_FILENO);
    }
    if (cmdt->outfile != NULL)
        dup2(exe->out_fd, STDOUT_FILENO);
    //tcsetattr(STDIN_FILENO, TCSANOW, env->sh_terminal);
    sigaction(SIGQUIT, &env->quit, NULL);
    exe->pid = fork();
    if (exe->pid < 0)
        return (1);
    else if (exe->pid == 0)
    {
        //if (is_buildins(cmdt->cmds->cmd_arr[0]))
        //    buildins(env, cmds->cmd_arr, exe);
        //else
        //{
            if (execve(find_path(cmdt->cmds->cmd_arr[0], env->env_path), cmdt->cmds->cmd_arr, NULL) == -1)
                printf("command not found");
        //}
    }
    else
        wait(NULL);
    //tcsetattr(STDIN_FILENO, TCSANOW, env->sh_terminal);
    return (0);
}