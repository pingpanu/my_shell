/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:23:39 by pingpanu          #+#    #+#             */
/*   Updated: 2023/03/15 14:57:01 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_strlen(const char *str)
{
	  const char      *s;

	  s = str;
	  while (*s != '\0')
		  ++s;
	  return (s - str);
}
