/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/31 17:04:35 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd_name)
{
	int	ret;

	if (ms_strcmp(cmd_name, "echo") == 0)
		ret = ECHO;
	else if (ms_strcmp(cmd_name, "cd") == 0)
		ret = CD;
	else if (ms_strcmp(cmd_name, "pwd") == 0)
		ret = PWD;
	else if (ms_strcmp(cmd_name, "export") == 0)
		ret = EXPORT;
	else if (ms_strcmp(cmd_name, "unset") == 0)
		ret = UNSET;
	else if (ms_strcmp(cmd_name, "env") == 0)
		ret = ENV;
	else if (ms_strcmp(cmd_name, "exit") == 0)
		ret = EXIT;
	else
		ret = NO_BUILTIN;
	return (ret);
}

void	do_builtin(int name, int argc, char *argv[])
{
	if (name == ECHO)
		echo(argc, argv);
	else if (name == CD)
		cd(argc, argv);
	else if (name == PWD)
		pwd();
	else if (name == EXPORT)
		builtin_export(argc, argv);
	else if (name == UNSET)
		builtin_unset(argc, argv);
	else if (name == ENV)
		env();
	else if (name == EXIT)
		builtin_exit(argc, argv);
}

void	func(t_cmd *cmd)
{
	extern char		**environ;
	char			**argv;
	t_list			*current;
	size_t			len;
	size_t			i;
	int				ret;

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

	ret = is_builtin(argv[0]);
	if (ret != NO_BUILTIN)
	{
		do_builtin(ret, len, argv);
		exit(0);
	}
	else if (execve(argv[0], argv, environ) < 0)
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
