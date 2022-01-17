/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:29:51 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/08 11:33:10 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
