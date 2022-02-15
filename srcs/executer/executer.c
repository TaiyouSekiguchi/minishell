/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/15 15:20:22 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	executer(t_list *cmds)
{
	int			cmd_count;
	t_cmd		*first_cmd_group;
	char		*first_cmd;
	t_list		*last_cmds;
	pid_t		ret;
	int			status;

	first_cmd_group = cmds->content;
	first_cmd = first_cmd_group->cmd->content;
	cmd_count = ms_lstsize(cmds);
	if (is_builtin(first_cmd) && cmd_count == 1)
	{
		do_exec(first_cmd_group);
	}
	else
	{
		last_cmds= ms_lstlast(cmds);
		ret = fork();
		if (ret == 0)
			do_pipe(last_cmds);
		else
		{
			wait(&status);
			g_status = WEXITSTATUS(status);
		}
	}
}
