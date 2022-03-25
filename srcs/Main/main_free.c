#include "minishell.h"

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

void	main_free(t_dir *info)
{
	free(info->pwd);
	free(info->old_pwd);
	free_my_env(info->my_env);
}

void	do_process_free(t_list **token_list, t_list **cmd_info_list)
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
