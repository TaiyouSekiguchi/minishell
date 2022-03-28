#include "minishell.h"

static char	*add_choice(t_kind kind, t_kind next_kind, t_list *current)
{
	char	*add;

	add = NULL;
	if (kind != CMD && current->next == NULL)
		add = ms_strdup("`newline'");
	else if (kind == PIPE && next_kind == PIPE)
		add = ms_strdup("`|'");
	else if (kind != CMD && kind != PIPE)
	{
		if (next_kind == INFILE)
			add = ms_strdup("`<'");
		else if (next_kind == HEREDOC)
			add = ms_strdup("`<<'");
		else if (next_kind == OUTFILE)
			add = ms_strdup("`>'");
		else if (next_kind == APPEND)
			add = ms_strdup("`>>'");
		else if (next_kind == PIPE)
			add = ms_strdup("`|'");
	}
	return (add);
}

static int	error_put(char *add)
{
	char	*msg;

	set_g_status_exception(258);
	msg = ms_strjoin("syntax error near unexpected token ", add);
	put_error_exit(NULL, msg, FALSE);
	ms_free(msg);
	ms_free(add);
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
