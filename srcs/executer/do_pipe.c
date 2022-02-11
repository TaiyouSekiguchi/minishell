/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:48:22 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/03 16:00:45 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
pipe_handler(int fd_1, int fd_2, int io)
{
	close(fd_1);
	dup2(fd_2, io);
	close(fd_2);
}

void
do_pipe(t_list *cmds)
{
	int		pp[2];
	pid_t	ret;

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
			pipe_handler(pp[0], pp[1], 1);
			/*close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);*/
			do_pipe(cmds->prev);
		}
		else
		{
			pipe_handler(pp[1], pp[0], 0);
			/*close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);*/
			do_exec(cmds->content);
		}
	}
}
