/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:41:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 18:24:10 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_init(t_cmd **cmd)
{
	*cmd = (t_cmd *)ms_xmalloc(sizeof(t_cmd));
	(*cmd)->cmd = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
}

static void	redirect_parse(t_list **current, int kind, t_cmd *cmd)
{
	char	*token;
	char	*prefix;
	char	*tmp;

	*current = (*current)->next;
	token = (char *)((*current)->content);
	if (kind == INFILE || kind == HEREDOC)
	{
		if (kind == INFILE)
			prefix = "< ";
		else
			prefix = "<< ";
		tmp = ms_strjoin(prefix, token);
		ms_lstadd_back(&cmd->infile, ms_lstnew(tmp));
	}
	else if (kind == OUTFILE || kind == APPEND)
	{
		if (kind == OUTFILE)
			prefix = "> ";
		else
			prefix = ">> ";
		tmp = ms_strjoin(prefix, token);
		ms_lstadd_back(&cmd->outfile, ms_lstnew(tmp));
	}
}

static void	parse_loop(t_list **cmds, t_list *tokens)
{
	t_cmd	*cmd;
	t_list	*current;
	t_kind	kind;
	char	*tmp;

	cmd_init(&cmd);
	current = tokens;
	while (current != NULL)
	{
		kind = token_kind(current->content);
		if (kind == CMD)
		{
			tmp = ms_strdup(current->content);
			ms_lstadd_back(&cmd->cmd, ms_lstnew(tmp));
		}
		else if (kind == PIPE)
		{
			ms_lstadd_back(cmds, ms_lstnew(cmd));
			cmd_init(&cmd);
		}
		else
			redirect_parse(&current, kind, cmd);
		current = current->next;
	}
	ms_lstadd_back(cmds, ms_lstnew(cmd));
}

void	parser(t_list **cmds, t_list *tokens)
{
	if (!syntax_check(tokens))
		return ;
	parse_loop(cmds, tokens);
}
