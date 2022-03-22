#include "minishell.h"

int	main(void)
{
	char	*input;
	t_dir	info;

	init(&info);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
	main_free(input, &info);
	ms_putendl_fd("exit", STDERR);
	return (get_g_status());
}
