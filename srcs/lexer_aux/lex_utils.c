#include "minishell.h"
#include "lexer.h"

void    add_cmd(t_list **lst, t_stpar *p, char *str, int n)
{
    char    *substr;

    substr = NULL;
    if (n == 0)
        substr = ft_substr(str, p->l, (p->r - p->l));
    else
        substr = ft_substr(str, p->l, (p->r - p->l + 1));
    if ((*lst)->next)
        ft_lstadd_after(lst, ft_lstnew(ft_strdup(substr)));
    else
        ft_lstadd_back(lst, ft_strnew(ft_strdup(substr)));
    if (n == 1)
        p->r++;
    p->l = p->r;
}

int     check(char cur, char adj_r, t_stpar p)
{
    if (ft_isquote(cur) && (p.r == p.len -1))
        return (1);
    else if (ft_isquote(cur) && ft_isspace(adj_r))
        return (1);
    else
        return (0);
}

void	init_stpar(t_stpar *stpar, char *str)
{
	stpar->len = ft_strlen(str);
	stpar->l = 0;
	stpar->r = 0;
}

int     metachar_num(char *str)
{
    int     i;
    int     ret;

    i = -1;
    ret = 0;
    while (str[++i])
    {
        if (str[i] == '<' || str[i] == '>' || str[i] == '|')
            ret++;
    }
    return (ret);
}