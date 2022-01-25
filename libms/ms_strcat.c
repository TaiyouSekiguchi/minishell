/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:21:49 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/24 15:25:07 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_strcat(char **dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = ms_strlen(*dst);
	j = 0;
	while (src[j] != '\0')
	{
		(*dst)[i + j] = src[j];
		j++;
	}
	(*dst)[i + j] = '\0';
}
