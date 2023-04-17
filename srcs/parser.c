/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:46:53 by pingpanu          #+#    #+#             */
/*   Updated: 2023/04/17 14:29:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_table	*start_parse(void)
{
	t_cmd_table	*ret;

	ret = malloc(sizeof(t_cmd_table));
	if (!ret)
		return (NULL);
	ret->cmds = NULL;
	ret->infile = NULL;
	ret->outfile = NULL;
	return (ret);
}

static void	run_parser(t_cmd_table *cmd_table, t_list **r, t_list **l)
{
	t_list	*temp;

	temp = NULL;
	redirection_parse(*r, cmd_table);
	temp = sub_linklist(*l, *r);
	node_addback(&cmd_table->cmds, newnode(temp));
	if (temp != NULL)
		free(temp);
	*l = (*r)->next;
	if (isredirection(*r))
		*l = (*l)->next;
	free((*r)->token);
}

t_cmd_table	*parser(t_list *cmd_ll)
{
	t_cmd_table	*cmd_table;
	t_list		*left;
	t_list		*right;

	cmd_table = start_parse();
	left = cmd_ll;
	right = cmd_ll;
	while (right)
	{
		if (isredirection(right) || !ft_strncmp(right->token, "|", 2))
			run_parser(cmd_table, &right, &left);
		if (right->next == NULL)
			node_addback(&cmd_table->cmds, newnode(left));
		right = right->next;
	}
	return (cmd_table);
}
