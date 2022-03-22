#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		ms_putchar_fd('\n', STDOUT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_g_status(1);
	}
}

void	default_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
