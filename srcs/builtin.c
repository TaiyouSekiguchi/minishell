/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:38:18 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 15:38:39 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd_name)
{
	int	ret;

	if (ms_strcmp(cmd_name, "echo") == 0)
		ret = ECHO;
	else if (ms_strcmp(cmd_name, "cd") == 0)
		ret = CD;
	else if (ms_strcmp(cmd_name, "pwd") == 0)
		ret = PWD;
	else if (ms_strcmp(cmd_name, "export") == 0)
		ret = EXPORT;
	else if (ms_strcmp(cmd_name, "unset") == 0)
		ret = UNSET;
	else if (ms_strcmp(cmd_name, "env") == 0)
		ret = ENV;
	else if (ms_strcmp(cmd_name, "exit") == 0)
		ret = EXIT;
	else
		ret = NO_BUILTIN;
	return (ret);
}

void	do_builtin(int name, int argc, char *argv[])
{
	if (name == ECHO)
		builtin_echo(argc, argv);
	else if (name == CD)
		builtin_cd(argc, argv);
	else if (name == PWD)
		builtin_pwd(2);
	else if (name == EXPORT)
		builtin_export(argc, argv);
	else if (name == UNSET)
		builtin_unset(argc, argv);
	else if (name == ENV)
		builtin_env();
	else if (name == EXIT)
		builtin_exit(argc, argv);
}
