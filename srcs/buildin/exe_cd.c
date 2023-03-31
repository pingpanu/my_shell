#include "myshell.h"

int     exe_cd(t_system *env, char *path)
{
    char    *buf;
    char    *pwd;

    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        return (0);
    }
    else
    {
        buf = ft_strdup(env->dis_str);
        pwd = ft_strjoin(" ", path);
        env->dis_str = ft_strjoin(buf, pwd);
        if (!env->dis_str)
            return (1);
        free(buf);
        free(pwd);
    }
    return (0);
}