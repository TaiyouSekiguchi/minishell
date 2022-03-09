#include "minishell.h"

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


char	*expand(char *token, t_boolean in_heredoc, char **my_env)
{
	char	*value;
	char	*ret;
	t_quote	quote;
	char	*start;
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
				value = ms_getenv(my_env, val_name);
				free(val_name);
				if (value == NULL)
					value = ms_strdup("");

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
