#include "minishell.h"

char	*rl_gets(void)
{
	static char *line_read = (char *)NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}

	line_read = readline(">> ");
	if (line_read == NULL)
	{
		//改行がきになる
		ms_putendl_fd("exit", STDOUT);
		exit(g_status);
	}

	if (line_read && *line_read)
		add_history(line_read);

	return (line_read);
}

/*void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}*/
