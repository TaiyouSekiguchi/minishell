#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int	is_delimiter(char c)
{
	if ((c == '|') || (c == '<') || (c == '>'))
		return (TRUE);
	return (FALSE);
}

int	is_metachar(char c)
{
	if (is_blank(c) || is_delimiter(c))
		return (TRUE);
	return (FALSE);
}
