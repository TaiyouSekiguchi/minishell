/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:24:24 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 14:11:15 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(int	act)
{
	static char		*pwd;

	if (act == 1)
	{
		if (pwd != NULL)
		{
			free(pwd);
			pwd = NULL;
		}
		pwd = getenv("PWD");
		if (pwd == NULL)
			ms_error("pwd");
	}
	else if (act == 2)
	{
		ms_putendl_fd(pwd, STDOUT);
	}
}
