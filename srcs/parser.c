#include "myshell.h"

char    **ll_to_argv(t_list *cmd_ll)
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

char    **parser(t_list *cmd_ll)
{
    /*1) Check whether the next token is redirection*/
    /*2) Check whether the previous token is redirection*/
    /*3) Check if any prefix existed to activate expander*/
    /*4) Make command table by change the specific token to command table*/
    char    **argv_table; //to store cmd_ll as argv table, so it's compatible with my executor

    argv_table = ll_to_argv(cmd_ll);
    if (!argv_table)
        return (NULL);
    return (argv_table);
}