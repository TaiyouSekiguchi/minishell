/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:02 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/21 13:23:34 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*tmp;
	char	*cp1;
	char	*cp2;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	cp1 = (char *)s1;
	cp2 = (char *)s2;
	len = ms_strlen(cp1) + ms_strlen(cp2);
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	tmp = ret;
	while (*cp1 != '\0')
		*tmp++ = *cp1++;
	while (*cp2 != '\0')
		*tmp++ = *cp2++;
	*tmp = '\0';
	return (ret);
}
