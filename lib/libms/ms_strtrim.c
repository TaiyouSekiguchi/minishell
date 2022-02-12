/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:17:08 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (ms_strchr(set, (int)s1[i]) == NULL)
			break ;
		start++;
		i++;
	}
	i = ms_strlen(s1) - 1;
	while (i >= 0)
	{
		if (ms_strchr(set, (int)s1[i]) == NULL)
			break ;
		i--;
	}
	ret = ms_substr(s1, start, i + 1 - start);
	return (ret);
}
