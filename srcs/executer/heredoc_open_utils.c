#include "minishell.h"

void	stdin_reset(void)
{
	if (!isatty(0))
	{
		close(0);
		open("/dev/tty", O_RDONLY);
	}
}

char	*set_tmp_file_name(void)
{
	char	*tmp_file_name;
	char	*tty;

	tty = ms_strdup(ttyname(0));
	tty = ms_char_replace(tty, '/', '_');
	tmp_file_name = ms_strjoin("./tmp", tty);
	free(tty);
	return (tmp_file_name);
}

int	tmp_file_create(char *tmp_file_name)
{
	int	fd;

	fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
	{
		put_error_exit(tmp_file_name, NULL, FALSE);
		free(tmp_file_name);
		return (ERROR_FD);
	}
	return (fd);
}

int	tmp_file_open(char *tmp_file_name)
{
	int	fd;

	fd = open(tmp_file_name, O_RDONLY);
	if (fd < 0)
	{
		put_error_exit(tmp_file_name, NULL, FALSE);
		return (ERROR_FD);
	}
	return (fd);
}
