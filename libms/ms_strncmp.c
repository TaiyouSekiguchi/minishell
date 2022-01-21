/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:05 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:17:05 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	ms_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ucs1;
	unsigned char	*ucs2;
	size_t			i;

	ucs1 = (unsigned char *)s1;
	ucs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ucs1[i] != ucs2[i] || ucs2[i] == '\0')
			return (ucs1[i] - ucs2[i]);
		i++;
	}
	return (0);
}
