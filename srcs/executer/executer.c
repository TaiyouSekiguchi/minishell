
#include "minishell.h"

extern int g_status;

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

int
heredoc_open(char *token)
{
	int	fd;

	fd = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		ms_error("open");
	heredoc_loop(fd, token);
	close(fd);

	fd = open("./tmp", O_RDONLY);
	if (fd < 0)
		ms_error("open failed");

	unlink("./tmp");
	return (fd);
}

int
outfile_open(char *token)
{
	int	fd;
	
	printf("outfile_open\n");
	fd = open(&token[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ms_error("open failed");

	return (fd);
}

int
append_open(char *token)
{
	int	fd;

	printf("append_open\n");
	fd = open(&token[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ms_error("open failed");

	return (fd);
}
















int
redirect_file_open(char *token)
{
	int		fd;

	if (token[0] == '<' && token[1] == ' ')
		fd = infile_open(token);
	else if (token[0] == '<' && token[1] == '<')
		fd = heredoc_open(token);
	else if (token[0] == '>' && token[1] == ' ')
		fd = outfile_open(token);
	else
		fd = append_open(token);

	return (fd);
}

int
get_redirect_fd(t_list *token_list)
{
	int		fd;
	char	*token;

	fd = -1;
	token = NULL;
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token != NULL)
			fd = redirect_file_open(token);
		else
			fd = -1;
		token_list = token_list->next;
	}

	return (fd);
}

void	do_redirect(int infile_fd, int outfile_fd)
{
	if (infile_fd >= 0)
	{
		close(0);
		dup2(infile_fd, 0);
		close(infile_fd);
	}
	if (outfile_fd >= 0)
	{
		close(1);
		dup2(outfile_fd, 1);
		close(outfile_fd);
	}
}

void	do_cmd(t_cmd *cmd_group, t_boolean is_last)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	if (is_last == TRUE)
	{
		infile_fd = get_redirect_fd(cmd_group->infile);
		outfile_fd = get_redirect_fd(cmd_group->outfile);

		do_redirect(infile_fd, outfile_fd);
		do_exec(cmd_group);
	}

	if (pipe(pipe_fd) == -1)
		perror("minishell");
	pid = fork();
	if (pid == 0)
	{
		infile_fd = get_redirect_fd(cmd_group->infile);
		outfile_fd = get_redirect_fd(cmd_group->outfile);

		close(pipe_fd[0]);
		if (is_last != TRUE)
			dup2(pipe_fd[1], STDOUT_FILENO);

		do_redirect(infile_fd, outfile_fd);
		do_exec(cmd_group);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	tmp_exec(t_list *cmds)
{
	size_t	cmd_len;
	size_t	i;
	t_list *last_elem;

	last_elem = ms_lstlast(cmds);
	cmd_len = ms_lstsize(cmds);
	i = 0;
	while (i < cmd_len)
	{
		if (cmds == last_elem)
			do_cmd(cmds->content, TRUE);
		else
			do_cmd(cmds->content, FALSE);
		cmds = cmds->next;
		i++;
		wait(&g_status);
	}
}

void	executer(t_list *cmds)
{
	pid_t	ret;
	int		status;

	ret = fork();
	if (ret == 0)
	{
		tmp_exec(cmds);
	}
	else
	{
		wait(&status);
		g_status = WEXITSTATUS(status);
	}
}
