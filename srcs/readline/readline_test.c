/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:08:47 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/11 17:46:15 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*command;

	//signal(SIGINT, sig_handler);
	while (1)
	{
		command = rl_gets();
		printf("%s\n", command);
		if (ms_strcmp(command, "clear_history") == 0)
			rl_clear_history();
	}
	free(command);
	return (0);
}
