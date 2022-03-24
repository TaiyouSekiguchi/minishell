#include "minishell.h"

int	main(int argc, char *argv[])
{
	char	*input;
	t_dir	info;

	init(&info);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	if (argc == 1)
	{
		input = NULL;
		while (1)
		{
			input = ms_rl_gets();
			if (input == NULL)
				break ;
			do_process(input, &info);
			free(input);
			input = NULL;
		}
		ms_putendl_fd("exit", STDERR);
	}
	else if (argc == 3 && ms_strcmp("-c", argv[1]) == 0)
	{
		input = ms_strdup(argv[2]);
		if (input != NULL)
		{
			do_process(input, &info);
			free(input);
			input = NULL;
		}
	}
	main_free(&info);
	return (get_g_status());
}
