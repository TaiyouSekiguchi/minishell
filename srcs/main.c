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

void	print_list(t_list *list, char *kind)
{
	t_list	*current;

	printf("%-10s: ", kind);
	current = list;
	while (current != NULL)
	{
		printf("[%s] ", (char *)current->content);
		current = current->next;
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	printf("\n");
	print_list(cmd->cmd, "cmd");
	print_list(cmd->infile, "infile");
	print_list(cmd->outfile, "outfile");
	printf("\n\n");
}

void	print_cmds(t_list *cmds)
{
	t_list	*current;

	current = cmds;
	while (current != NULL)
	{
		print_cmd(current->content);
		current = current->next;
	}
}

void	do_process(char *str, t_dir *d_info)
{
	t_list	*tokens;
	t_list	*cmds;

	if (str[0] == '\0')
		return ;
	tokens = NULL;
	lexer(&tokens, str);
	cmds = NULL;
	parser(&cmds, tokens);
	expander(cmds);
	executer(cmds, d_info);
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
