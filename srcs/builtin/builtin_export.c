
#include "minishell.h"

static int	get_index_of_key(char *key, char **environ)
{
	char			**split;
	char			*env_key;
	int				index;
	size_t			i;

	index = -1;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ms_split(environ[i], '=');
		env_key = split[0];
		if (ms_strcmp(env_key, key) == 0)
		{
			index = i;
			ms_split_free(split);
			break ;
		}
		i++;
		ms_split_free(split);
	}
	return (index);
}

static int	get_environ_row(char **environ)
{
	int		row;

	row = 0;
	while (environ[row] != NULL)
		row++;
	return (row);
}

void	free_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

static void	put_env(char **my_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (my_env[i] != NULL)
	{
		ms_putstr_fd("declare -x ", STDOUT);
		tmp = ms_strchr(my_env[i], '=');
		if (tmp != NULL)
		{
			write(STDOUT, my_env[i], tmp - my_env[i]);
			ms_putstr_fd("=\"", STDOUT);
			ms_putstr_fd(tmp + 1, STDOUT);
			ms_putstr_fd("\"\n", STDOUT);
		}
		else
			ms_putendl_fd(my_env[i], STDOUT);
		i++;
	}
}

static t_boolean	is_key_value_validate(char *key_value)
{
	if ((*key_value != '_' && ms_isalpha(*key_value) == FALSE))
		return (FALSE);
	key_value++;
	while (*key_value && *key_value != '=' && *key_value != '+')
	{
		if (is_name(*key_value) == FALSE)
			return (FALSE);
		key_value++;
	}
	if (*key_value == '+' && *(key_value + 1) != '=')
		return (FALSE);
	return (TRUE);
}

static char	*get_key(char *key_value, t_boolean *is_append)
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
		return (key_value);
}

char	*get_value(char *key_value)
{
	char	*tmp;

	tmp = ms_strchr(key_value, '=');
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp + 1);
}

int	register_key_value(char *key_value, char ***environ)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		index;
	char	**new_env;
	int		i;
	t_boolean	is_append;

	if (is_key_value_validate(key_value) != TRUE)
	{
		tmp = ms_strappend(ms_strdup("`"), ms_strdup(key_value));
		tmp = ms_strappend(tmp, ms_strdup("\'"));
		tmp = ms_strappend(tmp, ms_strdup(": not a valid identifier"));
		put_error_exit("export", 0, tmp, FALSE);
		free(tmp);
		return (EXIT_FAILURE);
	}
	key = get_key(key_value, &is_append);
	value = get_value(key_value);
	index = get_index_of_key(key, *environ);
	if (index == -1)
	{
		new_env = ms_xmalloc(sizeof(char *) * (get_environ_row(*environ) + 2));
		i = 0;
		while ((*environ)[i] != NULL)
		{
			new_env[i] = ms_strdup((*environ)[i]);
			i++;
		}
		tmp = ms_strdup(key);
		tmp = ms_strjoin(ms_strjoin(tmp, "="), value);
		new_env[i] = ms_strdup(tmp);
		new_env[i + 1] = NULL;
		free_environ(*environ);
		*environ = new_env;
	}
	else
	{
		if (is_append == TRUE)
		{
			tmp = ms_strdup((*environ)[index]);
			tmp = ms_strjoin(tmp, value);
		}
		else
		{
			tmp = ms_strdup(key);
			tmp = ms_strjoin(ms_strjoin(tmp, "="), value);
		}
		free((*environ)[index]);
		(*environ)[index] = ms_strdup(tmp);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

int	builtin_export(int argc, char *argv[], char ***environ)
{
	int			i;
	int			ret;

	ret = EXIT_SUCCESS;
	if (argc == 1)
	{
		put_env(*environ);
		return (ret);
	}
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			if (ms_strcmp(argv[i], "") == 0)
			{
				i++;
				continue;
			}
			if (register_key_value(argv[i], environ) == EXIT_FAILURE)
				ret = EXIT_FAILURE;
			i++;
		}
		return (ret);
	}
}
