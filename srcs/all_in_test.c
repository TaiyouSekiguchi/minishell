#include "minishell.h"

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

	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

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
