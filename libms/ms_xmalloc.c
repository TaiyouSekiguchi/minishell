/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:23:29 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:35:47 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_xmalloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		ms_error("malloc failed");
	return (ret);
}
