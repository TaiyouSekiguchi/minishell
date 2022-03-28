#include "minishell.h"

static char	*add_choice(t_kind kind, t_kind next_kind, t_list *current)
{
	char	*add;

	add = NULL;
	if (kind != CMD && current->next == NULL)
		add = "`newline'";
	else if (kind == PIPE && next_kind == PIPE)
		add = "`|'";
	else if (kind != CMD && kind != PIPE)
	{
		if (next_kind == INFILE)
			add = "`<'";
		else if (next_kind == HEREDOC)
			add = "`<<'";
		else if (next_kind == OUTFILE)
			add = "`>'";
		else if (next_kind == APPEND)
			add = "`>>'";
		else if (next_kind == PIPE)
			add = "`|'";
	}
	return (add);
}

static int	error_put(char *add)
{
	char	*msg;

	set_g_status_exception(258);
	msg = ms_strjoin("syntax error near unexpected token ", add);
	put_error_exit(NULL, msg, FALSE);
	free(msg);
	return (0);
}

int	syntax_check(t_list	*token_list)
{
	t_list	*current;
	t_kind	kind;
	t_kind	next_kind;
	char	*add;

	current = token_list;
	while (current != NULL)
	{
		kind = token_kind(current->content);
		if (current->next != NULL)
			next_kind = token_kind(current->next->content);
		else
			next_kind = -1;
		add = add_choice(kind, next_kind, current);
		if (add != NULL)
			return (error_put(add));
		current = current->next;
	}
	return (1);
}
