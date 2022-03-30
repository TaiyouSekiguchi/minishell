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
	ms_free(val_name);
	if (value == NULL)
		value = ms_strdup("");
	while (**token != '\0' && is_name(**token))
		*token += 1;
	return (value);
}

char	*get_val_name(char *token)
{
	int		i;

	i = 0;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	return (ms_strndup(token, i));
}
