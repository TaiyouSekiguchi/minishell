/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:46 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:28:27 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static void	get_ret(int n, int order, char *ret)
{
	unsigned int	copy;
	int				num;
	int				i;

	i = 0;
	if (n < 0)
	{
		ret[i++] = '-';
		copy = n * -1;
	}
	else
		copy = n;
	while (order != 0)
	{
		num = copy / order;
		ret[i++] = num + '0';
		copy %= order;
		order /= 10;
	}
	ret[i] = '\0';
}

char	*ms_itoa(int n)
{
	char	*ret;
	int		copy;
	int		digit;
	int		order;

	copy = n;
	if (copy < 0)
		digit = 2;
	else
		digit = 1;
	order = 1;
	while (copy / 10 != 0)
	{
		copy /= 10;
		digit++;
		order *= 10;
	}
	ret = (char *)ms_xmalloc(sizeof(char) * (digit + 1));
	if (ret == NULL)
		return (NULL);
	get_ret(n, order, ret);
	return (ret);
}
