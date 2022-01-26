/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/26 15:05:33 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	do_exec(t_list *cmd)
{
	pid_t	ret;
	int		pp[2] = {};

	if (i == cmd_n - 1)
	{
		execvp(cmds[0][0], cmds[0]);
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

			do_exec();
		}
		else
		{
			close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);

			execvp(cmds[cmd_n-i-1][0], cmds[cmd_n-i-1]);
		}
	}
}*/

void	func(t_cmd *cmd)
{
	extern char		**environ;
	char			**argv;
	t_list			*current;
	size_t			len;
	size_t			i;

	len = ms_lstsize(cmd->cmd);
	argv = (char **)ms_xmalloc(sizeof(char *) * (len + 1));

	i = 0;
	current = cmd->cmd;
	while (current != NULL)
	{
		argv[i] = current->content;
		i++;
		current = current->next;
	}

	if (execve(argv[0], argv, environ) < 0)
	{
		ms_error("execve failed");
	}
}

void	do_exec(t_cmd *cmd)
{
	int		child;
	int		status;

	child = fork();
	if (child < 0)
		ms_error("fork failed");

	if (child == 0)
		func(cmd);
	else
	{
		if (wait(&status) < 0)
		{
			ms_error("wait");
		}
		printf("The child (pid = %d)\n", child);
		printf("existed with status (%d)\n", WEXITSTATUS(status));
	}
}

void	executer(t_list *cmds)
{
	t_list	*current;

	current = cmds;
	while (current != NULL)
	{
		do_exec(current->content);
		current = current->next;
	}
}
