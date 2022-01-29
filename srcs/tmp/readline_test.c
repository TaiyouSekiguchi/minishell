/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:08:47 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/28 16:02:57 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_nl(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\n')
			printf("nl exist!!\n");
		i++;
	}
}

int	main(void)
{
	char	*command;

	using_history();
	read_history(".my_history");
	while (1)
	{
		command = readline(">> ");
		add_history(command);
		printf("%s\n", command);
		is_nl(command);
		free(command);
	}
	write_history(".my_history");
	return (0);
}
