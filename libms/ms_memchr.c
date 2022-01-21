/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:54 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:54 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ucs;
	unsigned char	ucc;
	size_t			i;

	ucs = (unsigned char *)s;
	ucc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ucs[i] == ucc)
			return (&ucs[i]);
		i++;
	}
	return (NULL);
}
