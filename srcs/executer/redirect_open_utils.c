
#include "minishell.h"

extern int g_status;

int		infile_open(char *file_name)
{
	int	fd;

	fd = open(&file_name[2], O_RDONLY);
	if (fd < 0)
		perror("infile_open");
		//ms_error("infile_open");
	return (fd);
}

static t_boolean	exist_quote(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' || word[i] == '\"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void
heredoc_loop(int fd, char *token)
{
	char		*word;
	char		*line;
	t_boolean	quote;

	word = ms_strdup(&token[3]);
	quote = exist_quote(word);
	word = remove_quotation(word);
	while(1)
	{
		line = readline("heredoc > ");
		if (line == NULL || ms_strcmp(line, word) == 0)
			break ;

		if (quote == FALSE)
			line = expand(line, TRUE);

		ms_putendl_fd(line, fd);
		free(line);
	}
	free(word);
	free(line);
}

int	heredoc_open(char *token)
{
	int		fd;
	char	*tty;
	char	*tmp_file_name;

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
		ms_error("heredoc open");
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

	fd = open(&token[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("outfile_open");
		//ms_error("open failed");

	return (fd);
}

int
append_open(char *token)
{
	int	fd;

	fd = open(&token[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("appned_open");
		//ms_error("open failed");

	return (fd);
}
