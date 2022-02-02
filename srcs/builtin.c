/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:38:18 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 16:33:29 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	builtin_check(char	*cmd_name)
{
	t_builtin	result;

	if (ms_strcmp(cmd_name, "echo") == 0)
		result = ECHO;
	else if (ms_strcmp(cmd_name, "cd") == 0)
		result = CD;
	else if (ms_strcmp(cmd_name, "pwd") == 0)
		result = PWD;
	else if (ms_strcmp(cmd_name, "export") == 0)
		result = EXPORT;
	else if (ms_strcmp(cmd_name, "unset") == 0)
		result = UNSET;
	else if (ms_strcmp(cmd_name, "env") == 0)
		result = ENV;
	else if (ms_strcmp(cmd_name, "exit") == 0)
		result = EXIT;
	else
		result = NOT_BUILTIN;
	return (result);
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
