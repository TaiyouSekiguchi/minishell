/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:48:22 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 16:04:45 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipe(t_list *cmds)
{
	pid_t	ret;
	int		pp[2] = {};

	if (cmds->prev == NULL)
	{
		do_exec(cmds->content);
	}
	else
	{
		pipe(pp);
		ret = fork();

		if (ret == 0)
		{
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);

			do_pipe(cmds->prev);
		}
		else
		{
			close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);

			do_exec(cmds->content);
		}
	}
}
