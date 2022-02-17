#include "minishell.h"
/*
static t_kind
distinguish_redirect_kind(char	*str)
{
	t_kind	kind;

	if (str[0] == '<' && str[1] == ' ')
		kind = INFILE;
	else if (str[0] == '<' && str[1] == '<')
		kind = HEREDOC;
	else if (str[0] == '>' && str[1] == ' ')
		kind = OUTFILE;
	else
		kind = APPEND;
	return (kind);
}

int		infile_open(char *token)
{
	int	fd;

	fd = open(&token[2], O_RDONLY);
	if (fd < 0)
		ms_error("open");
	return (fd);
}

void
heredoc_loop(int fd, char *token)
{
	char	*line;

	while(1)
	{
		line = readline("heredoc > ");
		if (ms_strcmp(line, &token[3]) == 0)
			break ;
		ms_putendl_fd(line, fd);
		free(line);
	}
	free(line);
}

void
pipe_handler(int fd_1, int fd_2, int io)
{
	close(fd_1);
	dup2(fd_2, io);
	close(fd_2);
}

int
heredoc_open(char *token, int pipe_fd[])
{
	int	fd;

	fd = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		ms_error("open");
	dprintf(32, "%d\n", pipe_fd[1]);
	heredoc_loop(fd, token);
	close(fd);

	fd = open("./tmp", O_RDONLY);
	if (fd < 0)
		ms_error("open failed");

	unlink("./tmp");
	return (fd);
}

int
get_redirect_fd(char *token, int pipe_fd[])
{
	t_kind	kind;
	int		fd;

	kind = distinguish_redirect_kind(token);
	if (kind == INFILE)
		fd = infile_open(token);
	else
		fd = heredoc_open(token, pipe_fd);

	return (fd);
}

int		get_infile_fd(t_cmd *cmd_group, int pipe_fd[])
{
	int		fd;
	t_list	*infile;
	char	*token;

	fd = -1;
	infile = cmd_group->infile;
	token = NULL;

	while (infile != NULL)
	{
		token = infile->content;
		if (token != NULL)
			fd = get_redirect_fd(token, pipe_fd);
		else
			fd = -1;
		infile = infile->next;
	}

	return (fd);
}
//
//
//void
//do_pipe(t_list *cmds, int fd)
//{
//	int		pp[2];
//	pid_t	ret;
//	t_list	*prev_cmds;
//	char	*token;
//
//	token = NULL;
//	if (cmds->prev == NULL)
//	{
//		if (fd < 0)
//			fd = get_infile_fd(cmds->content, pp);
//		do_exec(cmds->content, fd);
//	}
//	else
//	{
//		pipe(pp);
//		ret = fork();
//		if (ret == 0)
//		{
//			prev_cmds = cmds->prev;
//			fd = get_infile_fd(prev_cmds->content, pp);
//			pipe_handler(pp[0], pp[1], 1);
//			do_pipe(cmds->prev, fd);
//		}
//		else
//		{
//			wait(NULL);
//			fd = get_infile_fd(cmds->content, pp);
//
//			pipe_handler(pp[1], pp[0], 0);
//			do_exec(cmds->content, fd);
//		}
//	}
//}
//
*/