/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:01 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/06 15:52:52 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strdup(const char *s1)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ms_strlen(s1);
	ret = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	i = 0;
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
