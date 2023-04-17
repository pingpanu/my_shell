/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:14:40 by pingpanu          #+#    #+#             */
/*   Updated: 2023/04/17 21:51:41 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_numdoll(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			ret++;
	}
	return (ret);
}

char	*mini_getenv(char *str, char **ev)
{
	int		i;
	int		len;
	char	*buf;

	i = -1;
	buf = ft_strjoin(str, "=");
	if (!buf)
		return (NULL);
	len = ft_strlen(buf);
	while (ev[++i])
	{
		if (!ft_strncmp(ev[i], buf, len))
		{
			free(buf);
			return (ev[i] + len);
		}
	}
	free(buf);
	return (NULL);
}
