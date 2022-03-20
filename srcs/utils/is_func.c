#include "minishell.h"

int	is_redirect(char c1, char c2)
{
	if ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>'))
		return (TRUE);
	return (FALSE);
}

int	is_heredoc(char *token)
{
	if (token[0] == '<' && token[1] == '<')
		return (TRUE);
	return (FALSE);
}

int	is_name(char c)
{
	if (ms_isdigit(c) || ms_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}
