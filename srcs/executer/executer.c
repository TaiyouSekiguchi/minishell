
#include "minishell.h"

extern int g_status;

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
get_redirect_fd(char *token)
{
	t_kind	kind;
	int		fd;

	kind = distinguish_redirect_kind(token);
	if (kind == INFILE)
		fd = infile_open(token);
	else if (kind == HEREDOC)
		fd = heredoc_open(token);
	else if (kind == OUTFILE)
		fd = outfile_open(token);
	else
		fd = append_open(token);

	return (fd);
}

int		get_infile_fd(t_list *infile)
{
	int		fd;
	char	*token;

	fd = -1;
	token = NULL;

	while (infile != NULL)
	{
		token = infile->content;
		if (token != NULL)
			fd = get_redirect_fd(token);
		else
			fd = -1;
		infile = infile->next;
	}

	return (fd);
}

int		get_outfile_fd(t_list *outfile)
{
	int		fd;
	char	*token;

	fd = -1;
	token = NULL;

	while (outfile != NULL)
	{
		token = outfile->content;
		if (token != NULL)
			fd = get_redirect_fd(token);
		else
			fd = -1;
		outfile = outfile->next;
	}

	return (fd);
}

void	do_cmd(t_cmd *cmd_group, t_boolean is_last)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	if (pipe(pipe_fd) == -1)
		perror("minishell");
	pid = fork();
	if (pid == 0)
	{
		//file open
		infile_fd = get_infile_fd(cmd_group->infile);
		outfile_fd = get_outfile_fd(cmd_group->outfile);

		close(pipe_fd[0]);
		if (is_last != TRUE)
			dup2(pipe_fd[1], STDOUT_FILENO);
		do_exec(cmd_group, infile_fd, outfile_fd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	executer(t_list *cmds)
{
	size_t	cmd_len;
	size_t	i;

	cmd_len = ms_lstsize(cmds);
	i = cmd_len;
	while (cmd_len)
	{
		if (cmd_len == 1)
			do_cmd(cmds->content, TRUE);
		else
			do_cmd(cmds->content, FALSE);
		cmds = cmds->next;
		cmd_len--;
		wait(&g_status);
	}
	//while (i)
	//{
		//wait(&g_status);
		//i--;
	//}
}
