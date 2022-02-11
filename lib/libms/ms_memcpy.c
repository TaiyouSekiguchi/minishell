/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:55 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:55 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ucdst;
	unsigned char	*ucsrc;
	size_t			i;

	if (n == 0 || dst == src)
		return (dst);
	ucdst = (unsigned char *)dst;
	ucsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ucdst[i] = ucsrc[i];
		i++;
	}
	return (dst);
}
