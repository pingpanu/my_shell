/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:35:00 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/16 22:53:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_io_cmdt(t_executor *exe, char *infile, char *outfile)
{
	if (infile)
		dup2(exe->in_fd, STDIN_FILENO);
	if (outfile)
		dup2(exe->out_fd, STDOUT_FILENO);
}

int	single_executor(t_data *data, t_executor *exe)
{
	t_cmd_table	*cmdt;

	cmdt = data->cmd_table;
	if ((exe->in_fd < 0 && cmdt->infile) || (exe->out_fd < 0 && cmdt->outfile))
	{
		perror("file not found\n");
		return (1);
	}
	dup_io_cmdt(exe, cmdt->infile, cmdt->outfile);
	exe->pid = fork();
	if (exe->pid < 0)
		return (1);
	else if (exe->pid == 0)
	{
		if (!ft_strncmp(data->cmd_table->cmds->cmd_arr[0], "echo", 5))
			exit(exe_echo(exe, data->cmd_table->cmds));
		if (exec(&data->my_env, cmdt->cmds))
			return (1);
	}
	while (waitpid(-1, NULL, 0) != -1)
	{
	}
	return (0);
}
