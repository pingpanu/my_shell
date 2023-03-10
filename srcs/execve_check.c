#include "myshell.h"

/*This is to play around execve to design parser*/

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

int main(int argc, char **argv, char **env)
{
    char    **env_path = ft_split(getenv("PATH"), ':');
    char    *path;
    pid_t   pid = fork();

    if (argc < 2)
        return (0);
    if (pid == -1) {
        printf("Can't fork process\n");
        return (1);
    }
    else if (pid == 0) {
        path = find_path(argv[1], env_path);
        if (path == NULL)
            return (1);
        if (execve(path, argv + 1, env) == -1)
            printf("Command %s not found\n", argv[1]);
    }
    else
        wait(NULL);
    return (0);
}