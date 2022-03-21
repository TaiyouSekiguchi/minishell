#include "minishell.h"

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
	static char	*line_read = (char *) NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline("heredoc > ");
	return (line_read);
}

static void	heredoc_loop(int fd, char *token, char **my_env)
{
	char		*word;
	char		*line;
	t_boolean	quote;

	line = NULL;
	word = ms_strdup(&token[3]);
	quote = exist_quote(word);
	word = remove_quotation(word);
	while (1)
	{
		if (line != NULL)
			free(line);
		line = rl_gets_heredoc();
		if (line == NULL || ms_strcmp(line, word) == 0)
			break ;
		if (quote == FALSE)
			line = expand_for_heredoc(line, my_env);
		ms_putendl_fd(line, fd);
	}
	free(word);
}

int	heredoc_open(char *token, char **my_env)
{
	int		fd;
	char	*tmp_file_name;

	stdin_reset();
	tmp_file_name = set_tmp_file_name();
	fd = tmp_file_create(tmp_file_name);
	if (fd == ERROR_FD)
		return (ERROR_FD);
	heredoc_loop(fd, token, my_env);
	close(fd);
	fd = tmp_file_open(tmp_file_name);
	unlink(tmp_file_name);
	free(tmp_file_name);
	return (fd);
}
