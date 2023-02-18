#include "libft.h"

char    *newtoken(char *str)
{
    if (ft_strncmp(str, ">", 2) == 0)
        return (ft_strdup("GREAT"));
    else if (ft_strncmp(str, "<", 2) == 0)
        return (ft_strdup("LESS"));
    else if (ft_strncmp(str, ">>", 3) == 0)
        return (ft_strdup("GREATGREAT"));
    else if (ft_strncmp(str, ">&", 3) == 0)
        return (ft_strdup("GREATAMP"));
    else if (ft_strncmp(str, "|", 2) == 0)
        return (ft_strdup("PIPE"));
    else if (ft_strncmp(str, "&", 2) == 0)
        return (ft_strdup("AMPERSAND"));
    else
        return (ft_strdup(str));
}

t_list  *ft_lstnew(void *content)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (!new || !content)
        return (NULL);
    new->token = newtoken((char *)content);
    new->next = NULL;
    return (new);
}