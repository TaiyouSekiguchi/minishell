/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:57 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 15:16:57 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		write(fd, s, ms_strlen(s));
		write(fd, "\n", 1);
	}
}
