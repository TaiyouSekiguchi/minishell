/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:09 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:31:26 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static char	*empty_string(void)
{
	char	*ret;

	ret = (char *)ms_xmalloc(sizeof(char));
	*ret = '\0';
	return (ret);
}

char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ms_strlen(s) <= start || len <= 0)
		return (empty_string());
	count = ms_strlen(s + start);
	if (count < len)
		len = count;
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
