#include "minishell.h"

int	infile_open(char *file_name)
{
	int	fd;

	fd = open(&file_name[2], O_RDONLY);
	if (fd < 0)
		put_error_exit(&file_name[2], NULL, FALSE);
	return (fd);
}

int	outfile_open(char *token)
{
	int	fd;

	fd = open(&token[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		put_error_exit(&token[2], NULL, FALSE);
	return (fd);
}

int	append_open(char *token)
{
	int	fd;

	fd = open(&token[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		put_error_exit(&token[3], NULL, FALSE);
	return (fd);
}
