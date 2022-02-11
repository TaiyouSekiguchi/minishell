/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_int_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:40 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:40 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	ms_int_check(unsigned int input, unsigned int num, int minus)
{
	unsigned int	limit_a;
	unsigned int	limit_b;
	unsigned int	tmp;

	tmp = INT_MAX;
	if (minus == 1)
		tmp++;
	limit_a = tmp / 10;
	limit_b = tmp % 10;
	if (input > limit_a || (input == limit_a && num > limit_b))
		return (0);
	return (1);
}
