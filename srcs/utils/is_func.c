/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:29:51 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/09 17:37:58 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int	is_delimiter(char c)
{
	if ((c == '|') || (c == '<') || (c == '>'))
		return (TRUE);
	return (FALSE);
}

int	is_metachar(char c)
{
	if (is_blank(c))
		return (TRUE);
	if (is_delimiter(c))
		return (TRUE);
	return (FALSE);
}

int	is_redirect(char c1, char c2)
{
	if ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>'))
		return (TRUE);
	return (FALSE);
}

int	is_heredoc(char *token)
{
	if (token[0] == '<' && token[1] == '<')
		return (TRUE);
	return (FALSE);
}

int	is_name(char c)
{
	if (ms_isdigit(c) || ms_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}
