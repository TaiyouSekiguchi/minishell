#include "minishell.h"

void	put_argv(char **argv, int i)
{
	while (argv[i] != NULL)
	{
		ms_putstr_fd(argv[i], STDOUT);
		i++;
		if (argv[i] != NULL)
			ms_putstr_fd(" ", STDOUT);
	}
}

int	builtin_echo(int argc, char *argv[])
{
	t_boolean		is_flag;
	size_t			i;

	if (argc == 1)
		ms_putchar_fd('\n', STDOUT);
	else
	{
		if (ms_strcmp(argv[1], "-n") == 0)
		{
			is_flag = TRUE;
			i = 2;
		}
		else
		{
			is_flag = FALSE;
			i = 1;
		}
		put_argv(argv, i);
		if (is_flag == FALSE)
			ms_putstr_fd("\n", STDOUT);
	}
	return (EXIT_SUCCESS);
}
