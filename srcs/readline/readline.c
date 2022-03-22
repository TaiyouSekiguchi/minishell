#include "minishell.h"

char	*ms_rl_gets(void)
{
	char	*line_read;

	line_read = NULL;
	line_read = readline(">> ");
	if (line_read == NULL)
		return (NULL);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
