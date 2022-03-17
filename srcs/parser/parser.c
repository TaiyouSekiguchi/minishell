#include "minishell.h"

static void	cmd_init(t_cmd_info **cmd_info)
{
	*cmd_info = (t_cmd_info *)ms_xmalloc(sizeof(t_cmd_info));
	(*cmd_info)->cmd = NULL;
	(*cmd_info)->redirect = NULL;
}

static void	redirect_parse(t_list **current, int kind, t_cmd_info *cmd_info)
{
	char	*token;
	char	*prefix;
	char	*tmp;

	*current = (*current)->next;
	token = (char *)((*current)->content);
	if (kind == INFILE)
		prefix = "< ";
	else if (kind == HEREDOC)
		prefix = "<< ";
	else if (kind == OUTFILE)
		prefix = "> ";
	else
		prefix = ">> ";
	tmp = ms_strjoin(prefix, token);
	ms_lstadd_back(&cmd_info->redirect, ms_lstnew(tmp));
}

static void	parse_loop(t_list **cmd_info_list, t_list *token_list)
{
	t_cmd_info	*cmd_info;
	t_list		*current;
	t_kind		kind;
	char		*tmp;

	cmd_init(&cmd_info);
	current = token_list;
	while (current != NULL)
	{
		kind = token_kind(current->content);
		if (kind == CMD)
		{
			tmp = ms_strdup(current->content);
			ms_lstadd_back(&cmd_info->cmd, ms_lstnew(tmp));
		}
		else if (kind == PIPE)
		{
			ms_lstadd_back(cmd_info_list, ms_lstnew(cmd_info));
			cmd_init(&cmd_info);
		}
		else
			redirect_parse(&current, kind, cmd_info);
		current = current->next;
	}
	ms_lstadd_back(cmd_info_list, ms_lstnew(cmd_info));
}

void	parser(t_list **cmd_info_list, t_list *token_list)
{
	*cmd_info_list = NULL;
	if (!syntax_check(token_list))
		return ;
	parse_loop(cmd_info_list, token_list);
}
