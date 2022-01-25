/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:54:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/25 14:19:20 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd_member(t_list **list)
{
	t_list	*current;
	char	*token;

	current = *list;
	while (current != NULL)
	{
		token = current->content;
		expand(&token);
		current->content = token;
		current = current->next;
	}
}

static void	expand_cmd_structure(t_cmd **cmd)
{
	expand_cmd_member(&(*cmd)->cmd);
	expand_cmd_member(&(*cmd)->infile);
	expand_cmd_member(&(*cmd)->outfile);
}

void	expander(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cmd;

	current = cmds;
	while (current != NULL)
	{
		cmd = current->content;
		expand_cmd_structure(&cmd);
		current = current->next;
	}
}
