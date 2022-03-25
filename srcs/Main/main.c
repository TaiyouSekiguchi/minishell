#include "minishell.h"

static void	exec_argv(char **argv, t_dir *info)
{
	char	*input;
	int		i;

	i = 2;
	while (argv[i] != NULL)
	{
		input = ms_strdup(argv[i]);
		if (input != NULL)
		{
			if (input[0] == '\0')
			{
				free(input);
				break ;
			}
			//printf("[COMMAND] : [%s]\n\n", input);
			do_process(input, info);
			free(input);
			input = NULL;
			ms_putstr_fd("\n", STDOUT);
		}
		i++;
	}
}

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
	else if (argc >= 2 && ms_strcmp("-c", argv[1]) == 0)
		exec_argv(argv, &info);
	main_free(&info);
	return (get_g_status());
}
