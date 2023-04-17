/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:33:51 by pingpanu          #+#    #+#             */
/*   Updated: 2023/04/17 21:51:20 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static char	*dollar_to_str(t_list *buf, t_data *data)
{
	t_list	*ptr;
	char	*buenv;
	char	*ret;

	ptr = buf;
	ret = NULL;
	while (ptr)
	{
		buenv = (char *) ptr->token;
		if (!ft_strncmp(buenv, "$?", 3))
			buenv = ft_itoa(data->exe_status);
		else if (buenv[0] == '$')
			buenv = mini_getenv(buenv + 1, data->my_env.env_cop);
		if (!ret)
			ret = ft_strdup(buenv);
		else
			ret = ft_strjoin(ret, buenv);
		ptr = ptr->next;
	}
	return (ret);
}

static char	*expand_dollar(char *cast, t_data *data)
{
	t_stpar	cpar;
	t_list	*buf;
	char	*substr;

	buf = NULL;
	init_stpar(&cpar);
	cpar.len = ft_strlen(cast);
	while (cpar.r <= cpar.len && cpar.l <= cpar.r)
	{
		if (cpar.r == 0 && cast[cpar.r] == '$')
			cpar.r++;
		if ((cpar.r != 0 && (cast[cpar.r] == '$' || cast[cpar.r] == ' '))
			|| (cast[cpar.l] == '$' && cpar.r == cpar.len))
		{
			substr = ft_substr(cast, cpar.l, (cpar.r - cpar.l));
			ft_lstadd_back(&buf, ft_lstnew(substr));
			cpar.l = cpar.r;
		}
		cpar.r++;
	}
	cast = dollar_to_str(buf, data);
	ft_lstclear(&buf, &free_token);
	return (cast);
}

static char	*quote_remove(void *content)
{
	char	*casted;
	char	*ret;
	int		i;

	i = 0;
	casted = (char *) content;
	ret = ft_calloc(sizeof(char), ft_strlen(casted) - 1);
	while (i < (int)ft_strlen(casted) - 2)
	{
		ret[i] = casted[i + 1];
		i++;
	}
	free(casted);
	return (ret);
}

void	expander(t_list **cmd_ll, t_data *data)
{
	t_list	*ptr;
	char	*casted;

	if (!(*cmd_ll))
		return ;
	ptr = *cmd_ll;
	while (ptr)
	{
		casted = (char *) ptr->token;
		if (casted[0] == 39)
		{
			ptr->token = (void *) quote_remove(casted);
		}	
		else if (casted[0] == 34)
		{
			casted = quote_remove(casted);
			if (get_numdoll(casted) > 0)
				ptr->token = (void *) expand_dollar(casted, data);
			else
				ptr->token = (void *) casted;
		}
		else if (get_numdoll(casted) > 0)
			ptr->token = (void *) expand_dollar(casted, data);
		ptr = ptr->next;
	}
}
