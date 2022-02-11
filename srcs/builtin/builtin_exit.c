/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:00:09 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/31 16:56:37 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(int argc, char *argv[])
{
	int	exit_code;

	if (argc > 2)
		ms_error("too many");
	if (argc == 2)
	{
		exit_code = ms_atoi(argv[1]);
		exit(exit_code);
	}
	else
	{
		exit(0);
	}
}
