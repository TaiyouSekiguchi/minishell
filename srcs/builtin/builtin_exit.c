
#include "minishell.h"

extern int g_status;

int	builtin_exit(int argc, char *argv[])
{
	int	exit_code;

	if (argc > 2)
		return (1);
	if (argc == 2)
	{
		exit_code = ms_atoi(argv[1]);
		exit(exit_code);
	}
	else
	{
		exit(g_status);
	}
	return (0);
}
