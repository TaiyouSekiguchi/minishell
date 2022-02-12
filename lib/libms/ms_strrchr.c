/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:07 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:17:07 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strrchr(const char *s, int c)
{
	char	*ret;
	char	cc;
	size_t	len;
	size_t	i;

	ret = NULL;
	cc = (char)c;
	len = ms_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == cc)
			ret = (char *)&s[i];
		i++;
	}
	return (ret);
}
