/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:32:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/23 13:05:17 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		ms_free(split[i]);
		i++;
	}
	ms_free(split);
}
