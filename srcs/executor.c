#include "myshell.h"

/*to be moved to executor_utils*/
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

/*it supposed to take struct called cmd_table*/
int     executor(t_system my_env, char **cmd)
{
    char    *path;
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return (1);
    else if (pid == 0)
    {
        path = find_path(cmd[0], my_env.env_path);
        if (path == NULL)
        {
            printf("%s: command not found\n", cmd[0]);
            return (1);
        }
        if (execve(path, cmd, NULL) == -1)
            return (1);
    }
    else
        wait(NULL);
    return (0);
}