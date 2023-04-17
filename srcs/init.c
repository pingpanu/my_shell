/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:03:21 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/16 22:59:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_terminal(t_system *env)
{
	env->term = (t_term *)malloc(sizeof(t_term));
	if (env->term == NULL)
		return (-1);
	tcgetattr(STDIN_FILENO, &env->term->minishell);
	tcgetattr(STDIN_FILENO, &env->term->shell);
	env->term->minishell.c_cflag &= ~ECHOCTL;
	env->term->shell.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->term->minishell);
	return (0);
}

void	init_stpar(t_stpar *stpar)
{
	stpar->len = 0;
	stpar->l = 0;
	stpar->r = 0;
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init(t_data *data, t_stpar *stpar, char **ev)
{
	data->cmd_str = NULL;
	data->cmd_ll = NULL;
	data->cmd_table = NULL;
	data->my_env.env_cop = ft_split_dup(ev);
	ft_bzero(data->my_env.dis_str, 499);
	ft_strlcat(data->my_env.dis_str, "Minishell@ ", 499);
	ft_strlcat(data->my_env.dis_str, curr_dir(), 499);
	ft_strlcat(data->my_env.dis_str, ": ", 499);
	init_terminal(&data->my_env);
	data->my_env.sigint.sa_handler = sig_handler;
	sigemptyset(&data->my_env.sigint.sa_mask);
	data->my_env.sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &data->my_env.sigint, NULL);
	data->my_env.sigquit.sa_handler = SIG_IGN;
	sigemptyset(&data->my_env.sigquit.sa_mask);
	data->my_env.sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &data->my_env.sigquit, NULL);
	init_stpar(stpar);
}
