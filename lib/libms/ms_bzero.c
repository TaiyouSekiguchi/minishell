/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:35 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:35 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_bzero(void *s, size_t n)
{
	unsigned char	*us;
	size_t			i;

	us = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		us[i] = '\0';
		i++;
	}
}
