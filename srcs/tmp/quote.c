#include "expander.h"

static void	quote_set(char c, t_quote *quote)
{
	if (*quote == NONE)
	{
		if (c == '\'')
			*quote = SINGLE;
		else if (c == '\"')
			*quote = DOUBLE;
	}
	else if (*quote == SINGLE)
	{
		if (c == '\'')
			*quote = NONE;
	}
	else if (*quote == DOUBLE)
	{
		if (c == '\"')
			*quote = NONE;
	}
}

static int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}
