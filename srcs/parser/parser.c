/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:41:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 18:03:20 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_init(t_cmd_info **cmd_info)
{
	*cmd_info = (t_cmd_info *)ms_xmalloc(sizeof(t_cmd_info));
	(*cmd_info)->cmd = NULL;
	(*cmd_info)->infile = NULL;
	(*cmd_info)->outfile = NULL;
}

static void	redirect_parse(t_list **current, int kind, t_cmd_info *cmd)
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

static void	parse_loop(t_list **cmd_info_list, t_list *tokens)
{
	t_cmd_info	*cmd_info;
	t_list		*current;
	t_kind		kind;
	char		*tmp;

	cmd_init(&cmd_info);
	current = tokens;
	while (current != NULL)
	{
		kind = token_kind(current->content);
		if (kind == CMD)
		{
			tmp = ms_strdup(current->content);
			ms_lstadd_back(&cmd_info->cmd, ms_lstnew(tmp));
		}
		else if (kind == PIPE)
		{
			ms_lstadd_back(cmd_info_list, ms_lstnew(cmd_info));
			cmd_init(&cmd_info);
		}
		else
			redirect_parse(&current, kind, cmd_info);
		current = current->next;
	}
	ms_lstadd_back(cmd_info_list, ms_lstnew(cmd_info));
}

void	parser(t_list **cmd_info_list, t_list *tokens)
{
	if (!syntax_check(tokens))
		return ;
	parse_loop(cmd_info_list, tokens);
}
