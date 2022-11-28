/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:32:21 by pingpanu          #+#    #+#             */
/*   Updated: 2022/10/21 18:46:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		join[i] = s1[i];
	printf("Join = %s\n", join);
	while (s2[j])
		join[i++] = s2[j++];
	printf("Join = %s\n", join);
	join[i] = '\0';
	//free (s1);
	return (join);
}

int		main(int argc, char **argv)
{
	char	*joined;

	if (argc == 2)
	{
		joined = ft_strjoin(NULL, argv[1]);
		printf("%s\n", joined);
	}
	else if (argc == 3)
	{
		joined = ft_strjoin(argv[1], argv[2]);
		printf("%s\n", joined);
	}
	else
		printf("invalid amount of arguments");
	return (0);
}