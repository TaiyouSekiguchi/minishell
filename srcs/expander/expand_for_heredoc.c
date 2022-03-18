#include "minishell.h"

char	*expand_g_status(char **token)
{
	*token += 1;
	return (ms_itoa(get_g_status()));
}

char	*expand_num(char **token)
{
	*token += 1;
	return (ms_strdup(""));
}

char	*expand_from_env(char **token, char **my_env)
{
	char	*value;
	char	*val_name;

	val_name = get_val_name(*token);
	value = ms_getenv(my_env, val_name);
	free(val_name);
	if (value == NULL)
		value = ms_strdup("");
	while (**token != '\0' && is_name(**token))
		*token += 1;
	return (value);
}

void	expand_part(char **token, char **my_env, char **ret, char **start)
{
	char	*value;

	*ret = ms_strappend(*ret, ms_strndup(*start, *token - *start));
	*token += 1;
	if (**token == '?')
		value = expand_g_status(token);
	else if (ms_isdigit(**token))
		value = expand_num(token);
	else
		value = expand_from_env(token, my_env);
	*ret = ms_strappend(*ret, value);
	*start = *token;
}

char	*expand_for_heredoc(char *token, char **my_env)
{
	char	*ret;
	char	*start;

	ret = ms_strdup("");
	start = token;
	while (*token != '\0')
	{
		if ((*token != '$')
			|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
			expand_part(&token, my_env, &ret, &start);
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	return (ret);
}
