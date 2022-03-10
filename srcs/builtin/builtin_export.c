
#include "minishell.h"

static int	get_index_of_key(char *key, char **environ)
{
	//extern char		**environ;
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
	//ms_split_free(split);
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

int	builtin_export(int argc, char *argv[], char ***environ)
{
	//extern char	**environ;
	char		*key;
	int			index;
	int			row;
	char		**new_env;
	int			i;

	if (argc == 1)
		return (1);

	//validation

	key = get_key(argv[1]);
	index = get_index_of_key(key, *environ);
	free(key);
	if (index == -1)
	{
		row = get_environ_row(*environ);
		new_env = (char **)ms_xmalloc(sizeof(char *) * (row + 1 + 1));
		i = 0;
		while ((*environ)[i] != NULL)
		{
			new_env[i] = ms_strdup((*environ)[i]);
			i++;
		}
		new_env[i] = ms_strdup(argv[1]);
		i++;
		new_env[i] = NULL;
		free_environ(*environ);
		*environ = new_env;
	}
	else
	{
		free((*environ)[index]);
		(*environ)[index] = ms_strdup(argv[1]);
	}
	return (0);
}
