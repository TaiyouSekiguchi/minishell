
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
		if (line == NULL || ms_strcmp(line, &token[3]) == 0)
			break ;
		ms_putendl_fd(line, fd);
		free(line);
	}
	free(line);
}

int	heredoc_open(char *token)
{
	int		fd;
	char	*tty;
	char	*tmp_file_name;

	//fd = 0がstdinじゃなかったときはstdinに変更
	if (!isatty(0))
	{
		close(0);
		open("/dev/tty", O_RDONLY);
	}

	tty = ms_strdup(ttyname(0));
	tty = ms_char_replace(tty, '/', '_');
	tmp_file_name = ms_strjoin("./tmp", tty);
	free(tty);

	fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(tmp_file_name);
		ms_error("open");
	}
	heredoc_loop(fd, token);
	close(fd);

	fd = open(tmp_file_name, O_RDONLY);
	if (fd < 0)
	{
		free(tmp_file_name);
		ms_error("open failed");
	}

	unlink(tmp_file_name);
	free(tmp_file_name);
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
