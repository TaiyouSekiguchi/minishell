#include "minishell.h"

void	do_process(char *input, t_dir *d_info)
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
