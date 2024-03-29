/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:12:58 by pingpanu          #+#    #+#             */
/*   Updated: 2023/04/17 21:13:09 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_size(char	**split)
{
	int	len;

	len = 0;
	while (split[len] != NULL)
		len++;
	return (len);
}

void	ft_split_free(char **words)
{
	int	i;

	if (words != NULL)
	{
		i = 0;
		while (words[i] != NULL)
		{
			free(words[i]);
			i++;
		}
		free(words);
	}
}

char	**ft_split_dup(char **words)
{
	char	**dup;
	int		size;
	int		i;

	if (words == NULL)
		return (NULL);
	size = ft_split_size(words);
	dup = malloc(sizeof(char **) * (size + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(words[i]);
		if (dup[i] == NULL)
		{
			ft_split_free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
