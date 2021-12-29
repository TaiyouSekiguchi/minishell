/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:08:47 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/12/29 17:18:53 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(command);
	}
	write_history(".my_history");
	
	return (0);
}
