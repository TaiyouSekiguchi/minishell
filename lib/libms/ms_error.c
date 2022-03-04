/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:19:42 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 18:13:18 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_error(char *msg)
{
	//ms_putendl_fd(msg, STDERR_FILENO);
	perror(msg);
	exit(EXIT_FAILURE);
}
