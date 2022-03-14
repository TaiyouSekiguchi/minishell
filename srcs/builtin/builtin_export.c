
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

static char	*get_key(char *argv)
{
	char	*key;
	char	**split;

	split = ms_split(argv, '=');
	key = ms_strdup(split[0]);
	ms_split_free(split);
	return (key);
}


static int	get_environ_row(char **environ)
{
	//extern char	**environ;
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

void	put_env(char **my_env)
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

t_boolean	is_key_validate(char *key)
{
	if ((*key != '_' && ms_isalpha(*key) == FALSE))
		return (FALSE);
	key++;
	while (*key && *key != '=')
	{
		if (is_name(*key) == FALSE)
			return (FALSE);
		key++;
	}
	return (TRUE);
}

int	register_key_value(char *key_value, char ***environ)
{
	char	*key;
	char	*tmp;
	int		index;
	char	**new_env;
	int		i;

	if (is_key_validate(key_value) != TRUE)
	{
		tmp = ms_strappend(ms_strdup("`"), ms_strdup(key_value));
		tmp = ms_strappend(tmp, ms_strdup("\'"));
		tmp = ms_strappend(tmp, ms_strdup(": not a valid identifier"));
		put_error_exit("export", 0, tmp, FALSE);
		free(tmp);
		return (EXIT_FAILURE);
	}
	key = get_key(key_value);
	index = get_index_of_key(key, *environ);
	free(key);
	if (index == -1)
	{
		new_env = ms_xmalloc(sizeof(char *) * (get_environ_row(*environ) + 2));
		i = 0;
		while ((*environ)[i] != NULL)
		{
			new_env[i] = ms_strdup((*environ)[i]);
			i++;
		}
		new_env[i] = ms_strdup(key_value);
		new_env[i + 1] = NULL;
		free_environ(*environ);
		*environ = new_env;
	}
	else
	{
		free((*environ)[index]);
		(*environ)[index] = ms_strdup(key_value);
	}
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
			if (register_key_value(argv[i], environ) == EXIT_FAILURE)
				ret = EXIT_FAILURE;
			i++;
		}
		return (ret);
	}
}
