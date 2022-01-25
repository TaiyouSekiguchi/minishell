/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:06:41 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/24 15:21:18 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_strcpy(char **dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = '\0';
}
