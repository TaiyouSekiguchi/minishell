#include "minishell.h"

t_list	*expand_cmd_info_element(t_list *list, char **my_env)
{
	t_list	*new_lst;
	t_list	*current;
	t_list	*tmp;
	char	*token;

	new_lst = NULL;
	current = list;
	while (current != NULL)
	{
		token = current->content;
		ms_lstadd_back(&new_lst, expand(token, my_env));
		tmp = new_lst;
		while (tmp != NULL)
		{
			tmp->content = remove_quotation(tmp->content);
			tmp = tmp->next;
		}
		current = current->next;
	}
	ms_lstclear(&list, free);
	return (new_lst);
}

void	expander(t_list *cmd_info_list, char **my_env)
{
	t_list		*current;
	t_cmd_info	*cmd_info;

	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		cmd_info->cmd = expand_cmd_info_element(cmd_info->cmd, my_env);
		current = current->next;
	}
}
