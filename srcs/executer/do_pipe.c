/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:48:22 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/16 13:23:50 by tsekiguc         ###   ########.fr       */
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
	//int		result;

	while(1)
	{
		//write(STDOUT, "heredoc > ", 10);
		//result = get_next_line(STDIN, &line);
		line = rl_gets_heredoc();
		if (ms_strcmp(line, &token[3]) == 0)
			break ;
		write(fd, line, ms_strlen(line));
		write(fd, "\n", 1);
		free(line);
		/*if (result == ERROR)
		{
			close(fd);
			ms_error("gnl failed");
		}
		else if (result == END)
			break ;
		else
		{
			if (ms_strcmp(line, &token[3]) == 0)
				break ;
			write(fd, line, ms_strlen(line));
			write(fd, "\n", 1);
		}*/
	}
}

static t_kind
distinguish_redirect_kind(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

int	file_open(char *token)
{
	t_kind	kind;
	int		fd;

	kind = distinguish_redirect_kind(token);
	if (kind == INFILE)
	{
		printf("this is infile zone\n");
		fd = open(&token[2], O_RDONLY);
		if (fd < 0)
			ms_error("open");
	}
	else
	{
		printf("this is heredoc zone\n");
		fd = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (fd < 0)
			ms_error("open");

		//exec heredoc
		heredoc_loop(fd, token);
		close(fd);

		fd = open("./tmp", O_RDONLY);
		if (fd < 0)
			ms_error("open failed");

		unlink("./tmp");
	}
	
	return (fd);
}


void
do_pipe(t_list *cmds, int fd)
{
	int		pp[2];
	pid_t	ret;
	t_list	*prev_cmds;
	t_cmd	*prev_cmd;
	t_list	*infile;
	char	*token;
	t_cmd	*cmd;

	if (cmds->prev == NULL)
	{
		printf("here1\n");
		if (fd != -1)
		{
			cmd = cmds->content;
			infile = cmd->infile;
			token = infile->content;
			fd = file_open(token);
		}

		do_exec(cmds->content, fd);
	}
	else
	{
		pipe(pp);
		ret = fork();
		if (ret == 0)
		{
			printf("here2\n");
			//cat << end
			//file open  heredocument
			prev_cmds = cmds->prev;
			prev_cmd = prev_cmds->content;
			infile = prev_cmd->infile;
			token = infile->content;
			printf("token : %s\n", token);

			fd = file_open(token);
			printf("fd : %d\n", fd);

			pipe_handler(pp[0], pp[1], 1);
			/*close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);*/
			do_pipe(cmds->prev, fd);
		}
		else
		{
			printf("here3\n");
			//grep << END
			wait(NULL);
			cmd = cmds->content;
			infile = cmd->infile;
			token = infile->content;
			printf("token : %s\n", token);
			
			fd = file_open(token);
			printf("fd : %d\n", fd);

			pipe_handler(pp[1], pp[0], 0);
			/*close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);*/
			do_exec(cmds->content, fd);
		}
	}
}
