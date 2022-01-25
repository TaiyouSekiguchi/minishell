/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:54:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/25 15:55:57 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_list_remake(t_list *cmd)
{
	t_list	*ret;
	t_list	*current;
	t_list	*tokens;

	ret = NULL;
	current = cmd;
	while (current != NULL)
	{
		tokens = NULL;
		lexer(&tokens, current->content);
		ms_lstadd_back(&ret, tokens);
		current = current->next;
	}
	ms_lstclear(&cmd, free);
	return (ret);
}

static void	expand_cmd_member(t_list **list)
{
	t_list	*current;
	char	*token;

	current = *list;
	while (current != NULL)
	{
		token = current->content;
		expand(&token);
		token = remove_quotation(token);
		current->content = token;
		current = current->next;
	}
}

static void	expand_cmd_structure(t_cmd **cmd)
{
	expand_cmd_member(&(*cmd)->cmd);
	expand_cmd_member(&(*cmd)->infile);
	expand_cmd_member(&(*cmd)->outfile);
	(*cmd)->cmd = cmd_list_remake((*cmd)->cmd);
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
