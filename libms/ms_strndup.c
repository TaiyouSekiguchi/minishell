/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:06 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:28:13 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strndup(const char *s1, size_t n)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (s1 == NULL || n == 0)
		return (NULL);
	len = ms_strlen(s1);
	if (len > n)
		len = n;
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
