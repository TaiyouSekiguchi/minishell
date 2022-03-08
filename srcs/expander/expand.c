#include "minishell.h"

static int	is_name(char c)
{
	if (ms_isdigit(c) || ms_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

char	*get_val_name(char *token)
{
	char	*val_name;
	int		i;

	i = 0;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	val_name = ms_strndup(token, i);
	return (val_name);
}

char	*expand(char *token, t_boolean in_heredoc)
{
	char	*value;
	char	*ret;
	t_quote	quote;
	char	*start;
	char	*tmp;
	char	*val_name;

	quote = NONE;
	ret = ms_strdup("");
	start = token;
	while (*token != '\0')
	{
		if (in_heredoc == FALSE && is_quote(*token))
		{
			quote = quote_set(*token, quote);
			token++;
		}
		else if (quote == SINGLE || *token != '$')
			token++;
		else
		{
			if (*(token + 1) != '?' && !is_name(*(token + 1)))
			{
				token++;
				continue ;
			}
			ret = ms_strappend(ret, ms_strndup(start, token - start));
			token++;
			if (*token == '?')
			{
				value = ms_itoa(get_g_status());
				token++;
			}
			else if (*token >= '0' && *token <= '9')
			{
				value = ms_strdup("");
				token++;
			}
			else
			{
				val_name = get_val_name(token);
				tmp = getenv(val_name);
				free(val_name);
				if (tmp == NULL)
					value = ms_strdup("");
				else
					value = ms_strdup(tmp);
				while (*token != '\0' && is_name(*token))
					token++;
			}
			ret = ms_strappend(ret, value);
			start = token;
		}
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	return (ret);
}
