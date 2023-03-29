#include "myshell.h"

static char *rem_str(char *str)
{
    char    *ret;
    int     i = 0;
    int     j = 0;
    int     len = ft_strlen(str) - 2;

    ret = ft_calloc(sizeof(char), len);
    while (str[++i] && j < len)
    {
        ret[j] = str[i];
        j++;
    }
    return (ret);
}

static void quote_remove(char **cmd_arr)
{
    int     i = 0;
    
    while (cmd_arr[i])
    {
        if (cmd_arr[i][0] == 39 || cmd_arr[i][0] == 34)
            cmd_arr[i] = rem_str(cmd_arr[i]);
        i++;
    }
}

void    expander(t_cmd_table *cmdt)
{
    t_cmd_node  *ptr;

    if (!cmdt->cmds)
        return ;
    ptr = cmdt->cmds;
    while (ptr)
    {
        quote_remove(ptr->cmd_arr);
        ptr = ptr->next;
    }
}