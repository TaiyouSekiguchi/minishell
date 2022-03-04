/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:28:32 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/03 17:30:44 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotation(char *token)
{
	char	*ret;
	size_t	len;
	t_quote	quote;
	size_t	i;
	size_t	j;

	len = ms_strlen(token);
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	quote = NONE;
	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (is_quote(token[i]))
		{
			if ((quote == NONE)
				|| (quote == SINGLE && token[i] == '\'')
				|| (quote == DOUBLE && token[i] == '\"'))
				quote_set(token[i++], &quote);
			else
				ret[j++] = token[i++];
				//i++;
		}
		else
			ret[j++] = token[i++];
	}
	ret[j] = '\0';
	free(token);
	return (ret);
}
