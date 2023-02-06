/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:38:51 by pingpanu          #+#    #+#             */
/*   Updated: 2023/02/06 15:07:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static t_token newtoken(char *substr)
{
    if (strncmp(substr, ">", 2) == 0)
        return (great);
    else if (strncmp(substr, "<", 2) == 0)
        return (less);
    else if (strncmp(substr, ">>", 3) == 0)
        return (greatgreat);
    else if (strncmp(substr, ">&", 3) == 0)
        return (greatamp);
    else if (strncmp(substr, "|", 2) == 0)
        return (piped);
    else if (strncmp(substr, "&", 2) == 0)
        return (ampersand);
    else
        return (word);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (void *)content;
	new->token = newtoken((char *)content);
	new->next = NULL;
	return (new);
}
