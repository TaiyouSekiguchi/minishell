
#include "minishell.h"

extern int g_status;

void	builtin_exit(int argc, char *argv[])
{
	int	exit_code;

	if (argc > 2)
		ms_error("too many");
	if (argc == 2)
	{
		exit_code = ms_atoi(argv[1]);
		exit(exit_code);
	}
	else
	{
		exit(g_status);
	}
}
