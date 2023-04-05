#include "myshell.h"

static void     replace_str(char *str, char *old, char *replace)
{
    char    *ptr;
    char    *torep;
    int     shift;

    ptr = ft_strnstr(str, old, 499);
    if (!ptr)
        return ;
    shift = ft_strlen(str) - ft_strlen(ptr);
    if (!ft_strncmp(replace, "../", 4) || !ft_strncmp(replace, "./", 3))
        torep = ft_strjoin(curr_dir(), ": ");
    else
        torep = ft_strjoin(replace, ": ");
    if (!torep)
        return ;
    ft_memmove(str + shift, torep, ft_strlen(torep) + 1);
    free(torep);
}

int     exe_cd(t_system *env, char *path)
{
    char    *buf;

    buf = ft_strdup(curr_dir());
    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        free(buf);
    }
    else
    {
        replace_str(env->dis_str, buf, path);
        free(buf);
    }
    return (0);
}