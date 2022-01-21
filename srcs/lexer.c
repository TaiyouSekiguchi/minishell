/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:51:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 17:05:21 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_set(char c, t_quote *quote)
{
	if (*quote == NONE)
	{
		if (c == '\'')
			*quote = SINGLE;
		else if (c == '\"')
			*quote = DOUBLE;
	}
	else if (*quote == SINGLE)
	{
		if (c == '\'')
			*quote = NONE;
	}
	else if (*quote == DOUBLE)
	{
		if (c == '\"')
			*quote = NONE;
	}
}

static void	add_tokens(t_list **tokens, char *cmd, size_t start, size_t *i)
{
	char	*tmp;

	if (start < *i)
	{
		tmp = ms_strndup(&cmd[start], *i - start);
		ms_lstadd_back(tokens, ms_lstnew(tmp));
	}
	if (is_delimiter(cmd[*i]))
	{
		if (is_redirect(cmd[*i], cmd[*i + 1]))
		{
			ms_lstadd_back(tokens, ms_lstnew(ms_strndup(&cmd[*i], 2)));
			*i += 1;
		}
		else
			ms_lstadd_back(tokens, ms_lstnew(ms_strndup(&cmd[*i], 1)));
	}
}

void	lexer(t_list **tokens, char *cmd)
{
	t_quote		quote;
	size_t		start;
	size_t		i;

	quote = NONE;
	start = 0;
	i = 0;
	while (cmd[i] != '\0' )
	{
		if (is_quote(cmd[i]))
			quote_set(cmd[i++], &quote);
		else if (quote != NONE || !is_metachar(cmd[i]))
			i++;
		else
		{
			add_tokens(tokens, cmd, start, &i);
			start = ++i;
		}
	}
	if (quote != NONE)
	{
		printf("quote is not close\n");
		exit(1);
	}
	add_tokens(tokens, cmd, start, &i);
}
