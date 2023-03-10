#include "myshell.h"

/*This is solution implemented in pipex*/
/*I want to use stat, lstat, and fstat instead*/
int     iscommand(char **path_arr, char *cmd)
{
	char	*proto_ret;
	char	*ret;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		proto_ret = ft_strjoin(path_arr[i], "/");
		ret = ft_strjoin(proto_ret, cmd);
		free(proto_ret);
		if (access(ret, F_OK) == 0)
			return (1);
		free(ret);
		i++;
	}
	return (0);
}

int     cmd_checker(t_system env, t_list *cmd_ll)
{
    t_list  *ptr;

    ptr = cmd_ll;
    while (ptr != NULL)
    {
        if (check_access(env.env_path, ptr->token)) {
            return (1);
        }
        ptr = ptr->next;
    }
    return (0);
}

char    **ll_to_argv(t_list *cmd_ll)
{
    char    **argv;
    int     i = 0;
    t_list  *ll_ptr = cmd_ll;

    argv = malloc(sizeof(char *) * (ft_lstsize(cmd_ll) + 1));
    while (ll_ptr != NULL)
    {
        argv[i++] = ft_strdup(cmd_ll->token);
        ll_ptr = ll_ptr->next;
    }
    argv[i] = NULL;
    return (argv);
}

void    parser(t_system env, t_list *cmd_ll)
{
    /*1) Check whether the cmd_ll have any command*/
    /*2) Check if option exist (have - or -- at the front of str)*/
    /*3) Check if any prefix existed to activate expander*/
    /*4) Make command table*/
    char    **argv_table; //to store cmd_ll as argv table, so it's compatible with my previous pipex

    /*if (!cmd_cheker(env, cmd_ll))
    {
        printf("%s: command not found\n", cmd_ll->token);
        return (NULL);
    }
    */
    argv_table = ll_to_argv(cmd_ll);
    //this print_arr is for testing
    int     i = -1;
    while(argv_table[++i])
        printf("argv[%d] = %s\n", i, argv_table[i]);
}