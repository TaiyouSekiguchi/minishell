
#include "minishell.h"

int	builtin_exit(int argc, char *argv[])
{
	if (argc > 2)
		return (1);
	if (argc == 2)
	{
		set_g_status(ms_atoi(argv[1]));
		exit(get_g_status());
	}
	else
	{
		exit(get_g_status());
	}
	return (0);
}
