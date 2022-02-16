/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:48:22 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/16 15:00:40 by tsekiguc         ###   ########.fr       */
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

static t_kind
distinguish_redirect_kind(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

char
*rl_gets_heredoc(void)
{
	char	*line_read;

	line_read = readline("heredoc > ");
	return (line_read);
}

void
heredoc_loop(int fd, char *token)
{
	char	*line;

	while(1)
	{
		line = rl_gets_heredoc();
		if (ms_strcmp(line, &token[3]) == 0)
			break ;
		ms_putendl_fd(line, fd);
		free(line);
	}
}

int
file_open(char *token)
{
	t_kind	kind;
	int		fd;

	kind = distinguish_redirect_kind(token);
	if (kind == INFILE)
	{
		//printf("File open kind : INFILE\n");
		fd = open(&token[2], O_RDONLY);
		if (fd < 0)
			ms_error("open");
	}
	else
	{
		//printf("File open kind : HEREDOC\n");
		fd = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (fd < 0)
			ms_error("open");

		heredoc_loop(fd, token);
		close(fd);

		fd = open("./tmp", O_RDONLY);
		if (fd < 0)
			ms_error("open failed");

		unlink("./tmp");
	}
	
	return (fd);
}

int		get_fd(t_cmd *cmd_group)
{
	int		fd;
	t_list	*infile;
	char	*token;

	infile = cmd_group->infile;
	token = NULL;

	if (infile != NULL)
		token = infile->content;
	printf("token : %s\n", token);
	if (token != NULL)
		fd = file_open(token);
	else
		fd = -1;

	return (fd);
}


void
do_pipe(t_list *cmds, int fd)
{
	int		pp[2];
	pid_t	ret;
	t_list	*prev_cmds;
	t_cmd	*prev_cmd_group;
	char	*token;
	t_cmd	*cmd_group;

	token = NULL;
	if (cmds->prev == NULL)
	{

		if (fd < 0)
		{
			cmd_group = cmds->content;
			fd = get_fd(cmd_group);
		}

		do_exec(cmds->content, fd);
	}
	else
	{
		pipe(pp);
		ret = fork();
		if (ret == 0)
		{
			prev_cmds = cmds->prev;
			prev_cmd_group = prev_cmds->content;
			fd = get_fd(prev_cmd_group);

			pipe_handler(pp[0], pp[1], 1);
			do_pipe(cmds->prev, fd);
		}
		else
		{
			wait(NULL);

			cmd_group = cmds->content;
			fd = get_fd(cmd_group);

			pipe_handler(pp[1], pp[0], 0);
			do_exec(cmds->content, fd);
		}
	}
}
