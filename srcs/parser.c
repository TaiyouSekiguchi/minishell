/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:41:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 18:04:01 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_init(t_cmd **cmd)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	(*cmd)->cmd = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
}

static void	redirect_parse(t_list **current, int kind, t_cmd *cmd)
{
	char	*token;
	char	*prefix;
	char	*tmp;

	(*current) = (*current)->next;
	token = (char *)((*current)->content);
	if (kind == INFILE || kind == HEREDOC)
	{
		if (kind == INFILE)
			prefix = "< ";
		else
			prefix = "<< ";
		tmp = ft_strjoin(prefix, token);
		ft_lstadd_back(&cmd->infile, ft_lstnew(tmp));
	}
	else if (kind == OUTFILE || kind == APPEND)
	{
		if (kind == OUTFILE)
			prefix = "> ";
		else
			prefix = ">> ";
		tmp = ft_strjoin(prefix, token);
		ft_lstadd_back(&cmd->outfile, ft_lstnew(tmp));
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
			tmp = ft_strdup(current->content);
			ft_lstadd_back(&cmd->cmd, ft_lstnew(tmp));
		}
		else if (kind == PIPE)
		{
			ft_lstadd_back(cmds, ft_lstnew(cmd));
			cmd_init(&cmd);
		}
		else
			redirect_parse(&current, kind, cmd);
		current = current->next;
	}
	ft_lstadd_back(cmds, ft_lstnew(cmd));
}

void	parser(t_list **cmds, t_list *tokens)
{
	if (!syntax_check(tokens))
		return ;
	parse_loop(cmds, tokens);
}
