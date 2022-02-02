/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:00:02 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/27 15:46:37 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int argc, char *argv[])
{
	int		flag;
	size_t	i;

	if (argc == 1)
		return ;
	if (ms_strcmp(argv[1], "-n") == 0)
	{
		flag = 1;
		i = 2;
	}
	else
	{
		flag = 0;
		i = 1;
	}
	while (argv[i] != NULL)
	{
		ms_putstr_fd(argv[i], STDOUT);
		i++;
		if (argv[i] != NULL)
			ms_putstr_fd(" ", STDOUT);
	}
	if (flag == 0)
		ms_putstr_fd("\n", STDOUT);
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
