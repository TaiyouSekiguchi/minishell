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
		ms_lstclear(&(cmd_info->redirect), free);
		current = current->next;
	}
	ms_lstclear(cmd_info_list, free);
}

static void	do_process(char *input, t_dir *d_info)
{
	t_list	*token_list;
	t_list	*cmd_info_list;

	if (input[0] == '\0')
		return ;
	lexer(&token_list, input);
	if (token_list == NULL)
		return ;
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

static void	free_my_env(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i] != NULL)
	{
		free(my_env[i]);
		i++;
	}
	free(my_env);
}

static void	main_free(char *input, t_dir *info)
{
	free(input);
	free(info->pwd);
	free(info->old_pwd);
	free_my_env(info->my_env);
}

int	main(void)
{
	char	*input;
	t_dir	info;

	//init関数としてまとめたい
	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);
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
