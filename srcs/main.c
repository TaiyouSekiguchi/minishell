#include "minishell.h"
/*
void end(void)__attribute__((destructor));

void end(void)
{
	system("leaks minishell");
}
*/

static void	do_process_free(t_list **token_list, t_list **cmd_info_list)
{
	t_list		*current;
	t_cmd_info	*cmd_info;

	ms_lstclear(token_list, free);
	current = *cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		ms_lstclear(&(cmd_info->cmd), free);
		ms_lstclear(&(cmd_info->infile), free);
		ms_lstclear(&(cmd_info->outfile), free);
		current = current->next;
	}
	ms_lstclear(cmd_info_list, free);
}

static void	do_process(char *command, t_dir *d_info)
{
	t_list		*token_list;
	t_list		*cmd_info_list;

	if (command[0] == '\0')
		return ;

	token_list = NULL;
	lexer(&token_list, command);
	if (token_list == NULL)
		return ;

	cmd_info_list = NULL;
	parser(&cmd_info_list, token_list);
	if (cmd_info_list == NULL)
	{
		ms_lstclear(&token_list, free);
		return ;
	}

	expander(cmd_info_list, d_info->my_env);
	executer(cmd_info_list, d_info);

	do_process_free(&token_list, &cmd_info_list);
}

int	main(void)
{
	char	*input_line;
	t_dir	info;

	//init関数としてまとめたい
	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	input_line = NULL;
	while (1)
	{
		input_line = rl_gets();
		do_process(input_line, &info);
		if (ms_strcmp(input_line, "clear_history") == 0)
			clear_history();
	}

	//main freeとしてまとめたい
	free(input_line);
	free(info.pwd);
	free(info.old_pwd);

	return (get_g_status());
}
