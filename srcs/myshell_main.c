/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:08:07 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/17 21:49:12 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

char	*curr_dir(void)
{
	char	pwd[1000];
	char	*ret;

	if (!getcwd(pwd, 999))
		return (NULL);
	ret = ft_strrchr(pwd, '/', 1);
	return (ret);
}

void	exit_shell(t_data *data, int s)
{
	if (s != 0)
		perror("Myshell");
	if (data->cmd_table)
		free_cmdtable(data);
	if (data->cmd_ll)
		ft_lstclear(&data->cmd_ll, &free_token);
	free_arr(data->my_env.env_cop);
	rl_clear_history();
	printf("exit\n");
	exit(s);
}

static int	check_input(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	else if (ft_isempty_str(str))
		return (0);
	else
		return (1);
}


int	main(void)
{
	t_data	data;

	init(&data, environ);
	while (1)
	{
		data.cmd_str = readline(data.my_env.dis_str);
		if (data.cmd_str == NULL)
			break ;
		if (!check_input(data.cmd_str))
		{
			free(data.cmd_str);
			continue ;
		}
		add_history(data.cmd_str);
		lexer(&data);
		data.cmd_table = parser(data.cmd_ll);
		executor(&data);
		free(data.cmd_str);
		free_cmdtable(&data.cmd_table);
		ft_lstclear(data.cmd_ll, &free_token);
	}
	exit_shell(&data, 0);
	return (0);
}
