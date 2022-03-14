#include "minishell.h"

int		infile_open(char *file_name)
{
	int	fd;

	fd = open(&file_name[2], O_RDONLY);
	if (fd < 0)
		put_error_exit(&file_name[2], get_g_status(), NULL, FALSE);
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

static char	*rl_gets_heredoc(void)
{
	static char *line_read = (char *)NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}

	line_read = readline("heredoc > ");
	return (line_read);
}

void	heredoc_loop(int fd, char *token, char **my_env)
{
	char		*word;
	char		*line;
	t_boolean	quote;

	word = ms_strdup(&token[3]);
	quote = exist_quote(word);
	word = remove_quotation(word);
	while(1)
	{
		line = rl_gets_heredoc();
		//line = readline("heredoc > ");
		if (line == NULL || ms_strcmp(line, word) == 0)
			break ;

		if (quote == FALSE)
			line = expand_line(line, TRUE, my_env);

		ms_putendl_fd(line, fd);
		free(line);
	}
	free(word);
	free(line);
}

int	heredoc_open(char *token, char **my_env)
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
		put_error_exit(tmp_file_name, get_g_status(), NULL, FALSE);
	}
	heredoc_loop(fd, token, my_env);
	close(fd);

	fd = open(tmp_file_name, O_RDONLY);
	if (fd < 0)
	{
		free(tmp_file_name);
		put_error_exit(tmp_file_name, get_g_status(), NULL, FALSE);
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
		put_error_exit(&token[2], get_g_status(), NULL, FALSE);
	return (fd);
}

int
append_open(char *token)
{
	int	fd;

	fd = open(&token[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		put_error_exit(&token[3], get_g_status(), NULL, FALSE);
		//ms_error("open failed");

	return (fd);
}
