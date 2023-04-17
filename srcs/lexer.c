/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:56:01 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/17 21:55:05 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void    space_sep(t_list **lst, char *str)
{
    t_stpar sp;

    init_stpar(&sp, str);
    while (sp.r < sp.len && sp.l <= sp.r)
    {
        if (ft_isspace(str[sp.r]))
            sp.r++;
        else if (ft_isquote(str[sp.r]))
        {
            sp.l = sp.r++;
            sp.r++;
            while (!check(str[sp.r], str[sp.r + 1], sp))
                sp.r++;
            add_cmd(lst, &sp, str, 1);
        }
        else
        {
            sp.l = sp.r;
            while (!ft_isspace(str[sp.r]))
                sp.r++;
            add_cmd(lst, &sp, str, 0);
        }
    }
}

static void     metachar_sep(t_list **lst)
{
    t_list  *ptr;
    t_stpar sp;
    char    *casted;

    ptr = (*lst);
    while (ptr)
    {
        casted = (char *)ptr->token;
        if (metachar_num(casted) > 0)
        {

        }
        ptr = ptr->next;
    }
}

void	lexer(t_data *data)
{
	space_sep(&data->cmd_ll, data->cmd_str);
	metachar_sep(&data->cmd_ll);
	dol_expand(&data->cmd_ll, data->my_env);
	quote_remove(&data->cmd_ll);
}
