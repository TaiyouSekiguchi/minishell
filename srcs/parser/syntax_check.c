#include "minishell.h"

int		syntax_check(t_list	*tokens)
{
	t_list	*current;

	current = tokens;
	while (current != NULL)
	{
		if (token_kind(current->content) != CMD)
		{
			if (current->next == NULL || token_kind(current->next->content) != CMD)
			{
				put_error_exit(NULL, get_g_status(), SYNTAX_ERROR_MSG, FALSE);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
