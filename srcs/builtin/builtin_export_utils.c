#include "minishell.h"

char	*get_key(char *key_value, t_boolean *is_append)
{
	char	*tmp;

	tmp = ms_strchr(key_value, '+');
	if (tmp != NULL && ms_strncmp(tmp, "+=", 2) == 0)
	{
		*is_append = TRUE;
		return (ms_substr(key_value, 0, tmp - key_value));
	}
	*is_append = FALSE;
	tmp = ms_strchr(key_value, '=');
	if (tmp != NULL)
		return (ms_substr(key_value, 0, tmp - key_value));
	else
		return (ms_strdup(key_value));
}

static int	get_environ_row(char **environ)
{
	int		row;

	row = 0;
	while (environ[row] != NULL)
		row++;
	return (row);
}

static char	*get_value(char *key_value)
{
	char	*tmp;

	tmp = ms_strchr(key_value, '=');
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp + 1);
}

void	export_new_word(char ***environ, char *key_value, t_boolean is_append)
{
	char	*key;
	char	*value;
	char	**new_env;
	char	*tmp;
	int		i;

	key = get_key(key_value, &is_append);
	value = get_value(key_value);
	new_env = ms_xmalloc(sizeof(char *) * (get_environ_row(*environ) + 2));
	i = 0;
	while ((*environ)[i] != NULL)
	{
		new_env[i] = ms_strdup((*environ)[i]);
		i++;
	}
	tmp = ms_strdup(key);
	tmp = ms_strappend(tmp, ms_strdup("="));
	tmp = ms_strappend(tmp, ms_strdup(value));
	new_env[i] = ms_strdup(tmp);
	new_env[i + 1] = NULL;
	ms_split_free(*environ);
	*environ = new_env;
	free(key);
}

void	export_exist_word(char ***environ, int index, char *key_value)
{
	char		*key;
	char		*value;
	char		*tmp;
	t_boolean	is_append;

	key = get_key(key_value, &is_append);
	value = get_value(key_value);
	if (is_append == TRUE)
	{
		tmp = ms_strdup((*environ)[index]);
		tmp = ms_strjoin(tmp, value);
	}
	else
	{
		tmp = ms_strdup(key);
		tmp = ms_strappend(tmp, ms_strdup("="));
		tmp = ms_strappend(tmp, ms_strdup(value));
	}
	free((*environ)[index]);
	(*environ)[index] = ms_strdup(tmp);
	free(key);
}
