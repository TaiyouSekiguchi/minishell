#include "minishell.h"

int		syntax_check(t_list	*token_list)
{
	t_list	*current;
	t_kind	kind;
	t_kind	next_kind;

	current = token_list;
	while (current != NULL)
	{
		kind = token_kind(current->content);
		if (current->next != NULL)
			next_kind = token_kind(current->next->content);

		if ((kind != CMD && current->next == NULL)
			|| (kind == PIPE && next_kind == PIPE)
			|| (kind != CMD && kind != PIPE && next_kind != CMD))
		{
			put_error_exit(NULL, get_g_status(), SYNTAX_ERROR_MSG, FALSE);
			return (0);
		}
		/*if (token_kind(current->content) != CMD)
		{
			if (current->next == NULL || token_kind(current->next->content) != CMD)
			{
				put_error_exit(NULL, get_g_status(), SYNTAX_ERROR_MSG, FALSE);
				return (0);
			}
		}*/
		current = current->next;
	}
	return (1);
}
