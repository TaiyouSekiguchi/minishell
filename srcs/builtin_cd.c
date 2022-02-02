/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:36 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 13:55:33 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(int argc, char *argv[])
{
	char	*home_path;
	int		ret;

	(void)argv;

	if (argc > 2)
		ms_error("cd failed");

	if (argc == 1)
	{
		home_path = search_environ("HOME");
		ms_putendl_fd(home_path, STDOUT);
		if (ms_strcmp(home_path, "") == 0)
			ms_error("cd: HOME nothing");
		ret = chdir(home_path);
		if (ret < 0)
		{
			ms_putendl_fd("cd failed", STDOUT);
		}
	}
	else
	{
		ret = chdir(argv[1]);
		if (ret < 0)
		{
			ms_putendl_fd("cd failed", STDOUT);
		}
	}
	ms_putendl_fd(argv[1], STDOUT);
}
