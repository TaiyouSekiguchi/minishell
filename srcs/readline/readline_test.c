/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:08:47 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/25 23:49:46 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		command = rl_gets();
		printf("%s\n", command);
		if (ms_strcmp(command, "clear_history") == 0)
			rl_clear_history();
	}
	ms_free(command);
	return (0);
}
