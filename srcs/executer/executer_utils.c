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
