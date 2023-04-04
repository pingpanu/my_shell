#include "myshell.h"

static char     *replace_str(char *str, char *old, char *replace)
{
    char    *ptr;
    char    *torep;
    int     shift;

    ptr = ft_strnstr(str, old, 499);
    if (!ptr)
        return (NULL);
    shift = ft_strlen(str) - ft_strlen(ptr);
    torep = ft_strjoin(replace, ": ");
    if (!torep)
        return (NULL);
    ft_memmove(str + shift, torep, ft_strlen(torep) + 1);
    return (str);
}

int     exe_cd(t_system *env, char *path)
{
    char    *buf;
    char    *new_prompt;

    buf = ft_strdup(curr_dir());
    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        free(buf);
    }
    else
    {
        printf("curr dir = %s\n", buf);
        new_prompt = replace_str(env->dis_str, buf, path);
        printf("new prompt = %s\n", new_prompt);
        free(buf);
        ft_strlcpy(env->dis_str, new_prompt, 499);
    }
    return (0);
}