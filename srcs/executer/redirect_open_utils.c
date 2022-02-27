
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

int	heredoc_open(char *token, int stdin_save)
{
	int	fd;

	//fd = 0がstdinじゃなかったときはstdinに変更
	if (!isatty(0))
	{
		close(0);
		dup2(stdin_save, 0);
	}

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
