/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:42:27 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 16:56:22 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	quote_set(char c, t_quote quote)
{
	if (quote == NONE)
	{
		if (c == '\'')
			return (SINGLE);
		else if (c == '\"')
			return (DOUBLE);
	}
	else if (quote == SINGLE)
	{
		if (c == '\'')
			return (NONE);
	}
	else if (quote == DOUBLE)
	{
		if (c == '\"')
			return (NONE);
	}
	return (quote);
}
