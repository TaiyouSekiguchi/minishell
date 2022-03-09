#include "minishell.h"

t_list	*cmd_relexer(t_list *old_cmd)
{
	t_list	*new_cmd;
	t_list	*current;
	t_list	*token_list;

	new_cmd = NULL;
	current = old_cmd;
	while (current != NULL)
	{
		token_list = NULL;
		lexer(&token_list, current->content);
		ms_lstadd_back(&new_cmd, token_list);
		current = current->next;
	}
	ms_lstclear(&old_cmd, free);
	return (new_cmd);
}

static void	expand_cmd_info_element(t_list **elem_list, char **my_env)
{
	t_list	*current;
	char	*token;
	char	*after_token;

	current = *elem_list;
	while (current != NULL)
	{
		token = current->content;
		if (!is_heredoc(token))
		{
			after_token = expand(token, FALSE, my_env);
			free(token);
			after_token = remove_quotation(after_token);
			current->content = after_token;
		}
		current = current->next;
	}
}

static void	expand_cmd_info(t_cmd_info **cmd_info, char **my_env)
{
	expand_cmd_info_element(&(*cmd_info)->cmd, my_env);
	expand_cmd_info_element(&(*cmd_info)->infile, my_env);
	expand_cmd_info_element(&(*cmd_info)->outfile, my_env);
	(*cmd_info)->cmd = cmd_relexer((*cmd_info)->cmd);
}

void	expander(t_list *cmd_info_list, char **my_env)
{
	t_list		*current;
	t_cmd_info	*cmd_info;

	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		expand_cmd_info(&cmd_info, my_env);
		current = current->next;
	}
}
