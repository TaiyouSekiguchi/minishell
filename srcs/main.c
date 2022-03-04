#include "minishell.h"

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_process(char *str, t_dir *d_info)
{
	t_list	*tokens;
	t_list	*cmd_info_list;

	if (str[0] == '\0')
		return ;
	tokens = NULL;
	lexer(&tokens, str);
	cmd_info_list = NULL;
	parser(&cmd_info_list, tokens);
	expander(cmd_info_list);
	executer(cmd_info_list, d_info);
}

int	main(void)
{
	char	*input_line;
	t_dir	info;

	init_dir_info(&info);
	init_shlvl();

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	input_line = NULL;
	while (1)
	{
		//input_line free??
		input_line = rl_gets();
		do_process(input_line, &info);
		if (ms_strcmp(input_line, "clear_history") == 0)
			clear_history();
	}

	free(input_line);
	free(info.pwd);
	free(info.old_pwd);
	return (g_status);
}
