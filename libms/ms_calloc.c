/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:29:41 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ms_xmalloc(size * count);
	ms_bzero(ret, count * size);
	return (ret);
}
