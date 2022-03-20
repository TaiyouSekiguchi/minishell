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

void	print_cmd(t_cmd_info *cmd)
{
	printf("\n");
	print_list(cmd->cmd, "cmd");
	print_list(cmd->redirect, "redirect");
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
	expander(cmds, d_info->my_env);
	print_cmds(cmds);
	printf("***********test************\n\n");
	executer(cmds, d_info);
}

int	main(void)
{
	char	*input_line;
	t_dir	info;

	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	input_line = NULL;
	while (1)
	{
		input_line = rl_gets();
		test(input_line, &info);
		//do_process(input_line, &info);
		if (ms_strcmp(input_line, "clear_history") == 0)
			clear_history();
	}

	//main freeとしてまとめたい
	free(input_line);
	free(info.pwd);
	free(info.old_pwd);

	return (get_g_status());
}
