#include "minishell.h"

static t_list	*expand_cmd_info_element(t_list *list, char **my_env)
{
	t_list	*new_lst;
	t_list	*current;
	char	*token;

	new_lst = NULL;
	current = list;
	while (current != NULL)
	{
		token = current->content;
		if (!is_heredoc(token))
		{
			if (new_lst == NULL)
				new_lst = expand(token, FALSE, my_env);
			else
				ms_lstadd_back(&new_lst, expand(token, FALSE, my_env));

			t_list	*tmp;

			tmp = new_lst;
			while (tmp != NULL)
			{
				if(!is_heredoc(tmp->content))
					tmp->content = remove_quotation(tmp->content);
				tmp = tmp->next;
			}
		}
		else
		{
			ms_lstadd_back(&new_lst, ms_lstnew(ms_strdup(token)));
		}
		current = current->next;
	}
	ms_lstclear(&list, free);
	return (new_lst);
}

/*static void	expand_cmd_info(t_cmd_info **cmd_info, char **my_env)
{
	(*cmd_info)->cmd = expand_cmd_info_element((*cmd_info)->cmd, my_env);
	(*cmd_info)->redirect = expand_cmd_info_element((*cmd_info)->redirect, my_env);
}*/

void	expander(t_list *cmd_info_list, char **my_env)
{
	t_list		*current;
	t_cmd_info	*cmd_info;

	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		cmd_info->cmd = expand_cmd_info_element(cmd_info->cmd, my_env);
		cmd_info->redirect = expand_cmd_info_element(cmd_info->redirect, my_env);
		//expand_cmd_info(&cmd_info, my_env);
		current = current->next;
	}
}
