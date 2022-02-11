/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:58 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_putnbr_fd(int n, int fd)
{
	unsigned int	copy;
	int				div;
	int				mod;

	if (n < 0)
	{
		write(fd, "-", 1);
		copy = n * -1;
	}
	else
		copy = n;
	mod = copy % 10 + '0';
	div = copy / 10;
	if (div > 0)
		ms_putnbr_fd(div, fd);
	write(fd, &mod, 1);
}
