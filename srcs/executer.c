/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 16:42:21 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_list *cmds)
{
	int			cmd_count;
	t_cmd		*first_cmd_group;
	t_builtin	result;
	t_list		*cmds_last;
	pid_t		ret;

	cmd_count = ms_lstsize(cmds);
	first_cmd_group = cmds->content;
	result = builtin_check(first_cmd_group->cmd->content);
	if (cmd_count == 1 && result != NOT_BUILTIN)
	{
		do_exec(first_cmd_group);
	}
	else
	{
		cmds_last = ms_lstlast(cmds);
		ret = fork();
		if (ret == 0)
			do_pipe(cmds_last);
		else
			wait(NULL);
	}
}
