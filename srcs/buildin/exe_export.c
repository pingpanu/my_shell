/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:45:58 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/17 21:10:08 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_export_str(char *str)
{
	int	i;
	int	equal;

	i = -1;
	equal = 0;
	while (str[++i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		if (str[i] == '=')
			equal++;
	}
	if (equal != 1)
		return (0);
	return (1);
}

static char	**add_env(char *newenv, char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	while (arr[i])
		i++;
	ret = ft_calloc(sizeof(char *), i + 2);
	if (!ret)
		return (NULL);
	i = -1;
	while (arr[++i])
		ret[i] = ft_strdup(arr[i]);
	ret[i] = ft_strdup(newenv);
	return (ret);
}

static int	env_exist(char *export, t_system *env)
{
	char	varname[100];
	int		i;

	ft_bzero(varname, 99);
	i = -1;
	while (export[++i] != '=')
		varname[i] = export[i];
	i = 0;
	while (env->env_cop[i])
	{
		if (!ft_strncmp(env->env_cop[i], varname, ft_strlen(varname)))
		{
			env->env_cop[i] = ft_strdup(export);
			return (1);
		}
		i++;
	}
	return (0);
}

int	exe_export(t_cmd_node *node, t_system *env)
{
	int		i;

	i = -1;
	if (!node->cmd_arr[1])
		print_env(env, i);
	else
	{
		if (node->cmd_arr[2])
			printf("export only support 1 arguments\n");
		else if (!check_export_str(node->cmd_arr[1]))
			printf("improper string format\n");
		else
		{
			if (!env_exist(node->cmd_arr[1], env))
				env->env_cop = add_env(node->cmd_arr[1], env->env_cop);
			if (!env->env_cop)
				return (1);
		}
	}
	return (0);
}
