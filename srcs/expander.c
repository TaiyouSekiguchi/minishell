/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:54:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/25 15:15:59 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotation(char *token)
{
	char	*ret;
	size_t	len;
	size_t	i;
	size_t	j;
	t_quote	quote;

	len = ms_strlen(token);
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	quote = NONE;
	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (quote == NONE)
		{
			if (is_quote(token[i]))
			{
				quote_set(token[i], &quote);
				i++;
			}
			else
			{
				ret[j] = token[i];
				i++;
				j++;
			}
		}
		else if (quote == SINGLE)
		{
			if (token[i] == '\'')
			{
				quote_set(token[i], &quote);
				i++;
			}
			else
			{
				ret[j] = token[i];
				i++;
				j++;
			}
		}
		else if (quote == DOUBLE)
		{
			if (token[i] == '\"')
			{
				quote_set(token[i], &quote);
				i++;
			}
			else
			{
				ret[j] = token[i];
				i++;
				j++;
			}
		}
	}
	ret[j] = '\0';
	free(token);
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
