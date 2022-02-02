/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:43:55 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 14:11:56 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	extern char **environ;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
	{
		ms_putendl_fd(environ[i], STDOUT);
		i++;
	}
}

/*int main(void)
{
	char	*test_1[] = {"cat", NULL};
	char	*test_2[] = {"cat", "taiyou", NULL};
	char	*test_3[] = {"cat", "taiyou", "sekiguchi", NULL};
	char	*test_4[] = {"cat", "-n", NULL};
	char	*test_5[] = {"cat", "-n", "taiyou", NULL};
	char	*test_6[] = {"cat", "-n", "taiyou", "sekiguchi", NULL};

	echo(1, test_1);
	echo(2, test_2);
	echo(3, test_3);
	echo(2, test_4);
	echo(3, test_5);
	echo(4, test_6);
	return (0);
}*/
