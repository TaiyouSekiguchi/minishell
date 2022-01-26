/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/26 16:09:25 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	argv[i] = NULL;

	if (execve(argv[0], argv, environ) < 0)
	{
		ms_putendl_fd(argv[0], STDERR_FILENO);
		perror("execve");
		ms_error("execve failed");
	}
}

void	do_pipe(t_list *cmds)
{
	pid_t	ret;
	int		pp[2] = {};

	if (cmds->prev == NULL)
	{
		func(cmds->content);
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

			func(cmds->content);
		}
	}
}

void	executer(t_list *cmds)
{
	pid_t	ret;
	t_list	*last;

	last = ms_lstlast(cmds);

	ret = fork();
	if (ret == 0)
		do_pipe(last);
	else
		wait(NULL);
}
