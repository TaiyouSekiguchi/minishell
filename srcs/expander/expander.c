/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:54:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 15:03:13 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_relexer(t_list *cmd)
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

static t_boolean	is_heredoc(char *token)
{
	if (token[0] == '<' && token[1] == '<')
		return (TRUE);
	return (FALSE);
}

static void	expand_cmd_member(t_list **list)
{
	t_list	*current;
	char	*token;

	current = *list;
	while (current != NULL)
	{
		token = current->content;
		if (!is_heredoc(token))
		{
			expand(&token, 0);
			token = remove_quotation(token);
			current->content = token;
		}
		current = current->next;
	}
}

static void	expand_cmd_info(t_cmd_info **cmd_info)
{
	expand_cmd_info_element(&(*cmd_info)->cmd);
	expand_cmd_info_element(&(*cmd_info)->infile);
	expand_cmd_info_element(&(*cmd_info)->outfile);

	(*cmd_info)->cmd = cmd_relexer((*cmd_info)->cmd);
}

void	expander(t_list *cmd_info_list)
{
	t_list		*current;
	t_cmd_info	*cmd_info;

	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		expand_cmd_info(&cmd_info);
		current = current->next;
	}
}
