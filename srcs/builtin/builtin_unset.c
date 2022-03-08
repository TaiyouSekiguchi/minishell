
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
	char	**split;
	char	*key;

	split = ms_split(argv, '=');
	key = ms_strdup(split[0]);
	ms_split_free(split);
	return (key);
}

int	builtin_unset(int argc, char *argv[], char ***environ)
{
	//extern char	**environ;
	char	*key;
	int		index;
	int		i;

	if (argc == 1)
		return (1);

	//validation

	key = get_key(argv[1]);
	index = get_index_of_key(key, *environ);
	free(key);
	if (index >= 0)
	{
		free((*environ)[index]);
		i = index;
		while ((*environ)[i] != NULL)
		{
			(*environ)[i] = (*environ)[i + 1];
			i++;
		}
	}
	return (0);
}
