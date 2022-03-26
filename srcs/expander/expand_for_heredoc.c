#include "minishell.h"

static void	expand_part(char **token, char **my_env, char **ret, char **start)
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
	char	*save;

	ret = ms_strdup("");
	start = token;
	save = token;
	while (*token != '\0')
	{
		if ((*token != '$')
			|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
			expand_part(&token, my_env, &ret, &start);
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	ms_free(save);
	return (ret);
}
