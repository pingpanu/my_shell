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

void    print_ll(t_list *temp)
{
    t_list  *ptr;

    ptr = temp;
    while (ptr)
    {
        printf("%s -> ", ptr->token);
        ptr = ptr->next;
    }
    printf("\n");
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

t_cmd_node  *lastnode(t_cmd_node *nodes)
{
    if (nodes == NULL)
        return (NULL);
    while (nodes->next != NULL)
        nodes = nodes->next;
    return (nodes);
}

void    node_addback(t_cmd_node *node, t_cmd_node *new)
{
    t_cmd_node  *tmp_nd;

    if (!new)
        return ;
    if (node == NULL)
        node = new;
    else
    {
        tmp_nd = lastnode(node);
        tmp_nd->next = new;
    }
}

t_cmd_table parser(t_list *cmd_ll)
{
    /*1) Check whether the next token is redirection*/
    /*2) Check whether the previous token is redirection*/
    /*3) Check if any prefix existed to activate expander*/
    /*4) Make command table by change the specific token to command table*/
    t_cmd_table     cmd_table; //to store cmd_ll as argv table, so it's compatible with my executor
    t_list          *left_ptr;
    t_list          *right_ptr;
    t_list          *temp;

    //cmd_table = malloc(sizeof(t_cmd_table));
    cmd_table.cmds = NULL;
    cmd_table.infile = NULL;
    cmd_table.outfile = NULL;
    left_ptr = cmd_ll;
    right_ptr = cmd_ll;
    while (right_ptr)
    {
        /*parse cmd when pipe*/
        if (isword(left_ptr) != 0)
            left_ptr = left_ptr->next;
        if (ft_strncmp(right_ptr->token, "PIPE", 5) == 0)
        {
            temp = sub_linklist(left_ptr, right_ptr);
            print_ll(temp);
            node_addback(cmd_table.cmds, newnode(temp));
            ft_lstclear(&temp);
            left_ptr = right_ptr;
        }
        right_ptr = right_ptr->next;
    }
    return (cmd_table);
}