#include "myshell.h"

char    **ll_to_strarr(t_list *cmd_ll)
{
    char    **argv;
    int     i = 0;
    t_list  *ll_ptr = cmd_ll;

    argv = malloc(sizeof(char *) * (ft_lstsize(cmd_ll) + 1));
    while (ll_ptr != NULL)
    {
        argv[i] = ft_strdup(ll_ptr->token);
        ll_ptr = ll_ptr->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

t_list  *sub_linklist(t_list *left, t_list *right)
{
    t_list  *ret;

    ret = NULL;
    while(left && ft_strncmp(left->token, right->token, ft_strlen(right->token)) != 0)
    {
        ft_lstadd_back(&ret, ft_lstnew(left->token));
        left = left->next;
    }
    return (ret);
}

t_cmd_node  *newnode(t_list *temp)
{
    t_cmd_node  *new;

    new = malloc(sizeof(t_cmd_node));
    if (!new || !temp)
        return (NULL);
    new->cmd_arr = ll_to_strarr(temp);
    new->next = NULL;
    return (new);
}

void    node_addback(t_cmd_node **node, t_cmd_node *new)
{
    t_cmd_node  *tmp_nd;
    
    if (!new)
        return ;
    if (*node == NULL)
        *node = new;
    else
    {
        tmp_nd = *node;
        while(tmp_nd->next != NULL)
            tmp_nd = tmp_nd->next;
        tmp_nd->next = new;
    }
}

int     isword(char *token)
{
    if (ft_strncmp(token, "GREAT", 6) == 0 || ft_strncmp(token, "LESS", 5) == 0 ||
        ft_strncmp(token, "GREATGREAT", 11) == 0 || ft_strncmp(token, "HDOC", 5) == 0 ||
        ft_strncmp(token, "PIPE", 5) == 0)
        return (1);
    return (0);
}

int     isleft(char *token)
{
    if (ft_strncmp(token, "LESS", 5) == 0 || ft_strncmp(token, "HDOC", 5) == 0)
        return (1);
    return (0);
}

int     isright(char *token)
{
    if (ft_strncmp(token, "GREAT", 6) == 0 || ft_strncmp(token, "GREATGREAT", 11) == 0)
        return (1);
    return (0);
}

t_cmd_table    *parser(t_list *cmd_ll)
{
    t_cmd_table     *cmd_table;
    t_list          *left_ptr;
    t_list          *right_ptr;
    t_list          *temp;

    cmd_table = malloc(sizeof(t_cmd_table));
    if (!cmd_table)
        return (NULL);
    cmd_table->cmds = NULL;
    cmd_table->infile = NULL;
    cmd_table->outfile = NULL;
    left_ptr = cmd_ll;
    right_ptr = cmd_ll;
    while (right_ptr)
    {
        if (isword(right_ptr->token))
        {
            temp = sub_linklist(left_ptr, right_ptr);
            node_addback(&cmd_table->cmds, newnode(temp));
            ft_lstclear(&temp);
            if (isleft(right_ptr->token))
                ft_lstadd_back(&cmd_table->infile, ft_lstnew(right_ptr->next->token));
            if (isright(right_ptr->token))
                ft_lstadd_back(&cmd_table->outfile, ft_lstnew(right_ptr->next->token));
            left_ptr = right_ptr->next;
            if (isleft(right_ptr->token) || isright(right_ptr->token))
                left_ptr = left_ptr->next;
        }
        if (right_ptr->next == NULL)
            node_addback(&cmd_table->cmds, newnode(left_ptr));
        right_ptr = right_ptr->next;
    }
    return (cmd_table);
}