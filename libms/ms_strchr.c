/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:59 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strchr(const char *s, int c)
{
	char	*ret;
	char	cc;
	size_t	len;
	size_t	i;

	ret = (char *)s;
	cc = (char)c;
	len = ms_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (ret[i] == cc)
			return (&ret[i]);
		i++;
	}
	return (NULL);
}
