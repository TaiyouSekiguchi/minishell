/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/31 22:08:23 by tsekiguc         ###   ########.fr       */
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

t_kind	infile_check(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}


void	do_redirection(char *tmp, t_kind kind)
{
	int		fd;
	int		fd_1;
	int		fd_2;
	int		result;
	char	*file;
	char	*line;
	char	*deli;

	if (kind == INFILE)
	{
		file = ms_strdup(&tmp[2]);
		fd = open(file, O_RDONLY);
		if (fd < 0)
			ms_error("open");
		close(0);
		dup2(fd, 0);
		close(fd);
	}
	else if (kind == HEREDOC)
	{
		deli = ms_strdup(&tmp[3]);
		fd_1 = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (fd_1 < 0)
			ms_error("open");
		
		while(1)
		{
			write(1, "heredoc > ", 10);
			result = get_next_line(0, &line);
			if (result == ERROR)
				ms_error("gnl failed");
			else if (result == END)
				break ;
			else
			{
				if (ms_strcmp(line, deli) == 0)
					break ;
				write(fd_1, line, ms_strlen(line));
				write(fd_1, "\n", 1);
			}
		}
		close(fd_1);

		fd_2 = open("./tmp", O_RDONLY);
		if (fd_2 < 0)
			ms_error("open failed");

		unlink("./tmp");

		close(0);
		if (dup2(fd_2, 0) < 0)
			ms_error("dup2 failed");
		close(fd_2);
	}
}

void	func(t_cmd *cmd)
{
	extern char		**environ;
	char			**argv;
	t_list			*current;
	size_t			len;
	size_t			i;
	int				ret;
	char			*tmp;
	t_kind			kind;

	current = cmd->infile;
	if (current != NULL)
	{
		tmp = ms_strdup(current->content);
		kind = infile_check(tmp);
		do_redirection(tmp, kind);
	}

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
