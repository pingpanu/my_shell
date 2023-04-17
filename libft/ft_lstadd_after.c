#include "libft.h"

void	ft_lstadd_after(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = (*lst)->next;
        (*lst)->next = new;
	}
}