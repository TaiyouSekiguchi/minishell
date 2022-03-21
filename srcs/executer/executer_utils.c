#include "minishell.h"

void	tty_reset(void)
{
	if (!isatty(0) && !isatty(1))
	{
		close(0);
		close(1);
		open("/dev/tty", O_RDONLY);
		open("/dev/tty", O_WRONLY);
	}
	else if (!isatty(0))
	{
		close(0);
		open("/dev/tty", O_RDONLY);
	}
	else
	{
		close(1);
		open("/dev/tty", O_WRONLY);
	}
}

void	do_redirect(t_fd *redirect_fd)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = redirect_fd->infile;
	outfile_fd = redirect_fd->outfile;
	if (infile_fd != NONE_FD)
	{
		close(STDIN);
		dup2(infile_fd, STDIN);
		close(infile_fd);
	}
	if (outfile_fd != NONE_FD)
	{
		close(STDOUT);
		dup2(outfile_fd, STDOUT);
		close(outfile_fd);
	}
}
