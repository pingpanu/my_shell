/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:47:31 by pingpanu          #+#    #+#             */
/*   Updated: 2023/02/18 14:52:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*ptr;
	t_list	*next;

	if (*lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	*lst = NULL;
}