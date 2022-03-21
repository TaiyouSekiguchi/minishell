#include "minishell.h"

void end(void)__attribute__((destructor));

void end(void)
{
    system("leaks minishell");
}


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
		input = rl_gets();
		if (input == NULL)
			break ;
		if (ms_strcmp(input, "history -c") == 0)
			clear_history();
		else
			do_process(input, &info);
	}
	main_free(input, &info);
	ms_putendl_fd("exit", STDERR);
	return (get_g_status());
}
