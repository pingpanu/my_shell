/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:24:40 by pingpanu          #+#    #+#             */
/*   Updated: 2022/03/10 23:47:07 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	no_of_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static int	wordlen(const char *s, int k, char c)
{
	int	len;

	len = 0;
	while (*(s + k) && *(s + k) != c)
	{
		k++;
		len++;
	}
	return (len);
}

char	**ft_error(char **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	words = no_of_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	k = 0;
	i = -1;
	len = 0;
	while (++i < words)
	{
		ft_strslice_c(s, c, k);
		if (!split[i])
			return (ft_error(split));
	}
	split[i] = NULL;
	return (split);
}
