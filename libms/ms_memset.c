/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:56 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:56 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_memset(void *b, int c, size_t len)
{
	unsigned char	*ub;
	unsigned char	uc;
	size_t			i;

	ub = (unsigned char *)b;
	uc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ub[i] = uc;
		i++;
	}
	return (b);
}
