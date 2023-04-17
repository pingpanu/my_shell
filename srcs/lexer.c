/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:56:01 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/17 14:29:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd(t_stpar *stpar, t_data *data, int n)
{
	char	*substr;

	substr = NULL;
	if (n == 0)
		substr = ft_substr(data->cmd_str, stpar->l, (stpar->r - stpar->l));
	else
		substr = ft_substr(data->cmd_str, stpar->l, (stpar->r - stpar->l + 1));
	//if (!(ft_isquote(substr[0]) && ft_strlen(substr) != 2))
	ft_lstadd_back(&data->cmd_ll, ft_lstnew(ft_strdup(substr)));
	free(substr);
	if (n == 1)
		stpar->r++;
	stpar->l = stpar->r;
}

static int	check(t_data *data, t_stpar stpar)
{
	int	space;

	space = ft_isspace(data->cmd_str[stpar.r]);
	if ((space == 0 && !ft_isquote(data->cmd_str[stpar.r]))
		&& stpar.r < stpar.len)
		return (1);
	return (0);
}

void	lexer(t_data *data, t_stpar stpar)
{
	stpar.len = ft_strlen(data->cmd_str);
	while (stpar.r < stpar.len && stpar.l <= stpar.r)
	{
		if (ft_isspace(data->cmd_str[stpar.r]))
		{
			stpar.r++;
			stpar.l++;
		}
		else if (ft_isquote(data->cmd_str[stpar.r]))
		{
			stpar.quote = data->cmd_str[stpar.r];
			stpar.r++;
			while (data->cmd_str[stpar.r] != stpar.quote && stpar.r < stpar.len)
				stpar.r++;
			add_cmd(&stpar, data, 1);
		}
		else
		{
			stpar.r++;
			while (check(data, stpar) == 1)
				stpar.r++;
			add_cmd(&stpar, data, 0);
		}
	}
	expander(&data->cmd_ll, data);
}