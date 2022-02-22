#include "minishell.h"

//int	g_status;

/*
char	*rl_gets(void)
{
	static char *line_read = (char *)NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}

	line_read = readline(">> ");

	if (line_read && *line_read)
		add_history(line_read);

	return (line_read);
}
*/

void	sig_handler(int signum)
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

void	test(char *str, t_dir *d_info)
{
	t_list	*tokens;
	t_list	*cmds;

	printf("***********test************\n");
	printf("[command] : %s\n", str);
	if (str[0] == '\0')
		return ;
	tokens = NULL;
	lexer(&tokens, str);
	cmds = NULL;
	parser(&cmds, tokens);
	expander(cmds);
	print_cmds(cmds);
	printf("***********test************\n\n");
	executer(cmds, d_info);
}

int	main(void)
{
	char	*command;
	t_dir	info;

	init_dir_info(&info);
	signal(SIGINT, sig_handler);
	while (1)
	{
		command = rl_gets();
		printf("%s\n", command);
		test(command, &info);
		if (ms_strcmp(command, "clear_history") == 0)
			clear_history();
			//rl_clear_history();
	}
	free(command);
	return (g_status);
}
