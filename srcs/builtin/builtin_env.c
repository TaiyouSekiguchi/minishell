#include "minishell.h"

int	builtin_env(char **environ)
{
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ms_strchr(environ[i], '=') != NULL)
			ms_putendl_fd(environ[i], STDOUT);
		i++;
	}
	return (0);
}
