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
		ms_putendl_fd("exit", STDOUT);
		exit(get_g_status());
	}

	if (line_read && *line_read)
		add_history(line_read);

	return (line_read);
}
