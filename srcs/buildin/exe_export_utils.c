/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:55:46 by pingpanu          #+#    #+#             */
/*   Updated: 2023/04/17 21:06:21 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	selection_sort(char **arr, int size)
{
	int	i;
	int	j;
	int	min_d;

	i = 0;
	while (i < size)
	{
		min_d = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(arr[j], arr[min_d], 999) < 0)
				min_d = j;
			j++;
		}
		swap(&arr[min_d], &arr[i]);
		i++;
	}
}

void	print_env(t_system *env, int i)
{
	char	**as_env;
	int		env_size;

	as_env = ft_split_dup(env->env_cop);
	env_size = ft_split_size(env->env_cop);
	selection_sort(as_env, env_size);
	i = -1;
	while (as_env[++i])
		printf("%s\n", as_env[i]);
	ft_split_free(as_env);
}
