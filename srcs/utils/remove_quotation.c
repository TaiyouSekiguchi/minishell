/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:28:32 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 16:48:39 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_last_quote(char c, t_quote quote)
{
	if ((quote == NONE)
		|| (quote == SINGLE && c == '\'')
		|| (quote == DOUBLE && c == '\"'))
		return (TRUE);
	else
		return (FALSE);
}

char	*remove_quotation(char *token)
{
	char	*ret;
	size_t	len;
	t_quote	quote;
	size_t	i;
	size_t	j;

	len = ms_strlen(token);
	ret = (char *)ms_calloc(len + 1, sizeof(char));
	quote = NONE;
	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (is_quote(token[i]) && is_last_quote(token[i], quote))
				quote_set(token[i++], &quote);
		else
			ret[j++] = token[i++];
	}
	ret[j] = '\0';
	free(token);
	return (ret);
}
