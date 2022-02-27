
#include "minishell.h"

static int
get_index_of_name_in_environ(char *name)
{
	extern char		**environ;
	char			**split;
	char			*env_name;
	char			*env_value;
	int				index;
	size_t			i;

	index = -1;
	split = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ms_split(environ[i], '=');
		env_name = split[0];
		env_value = split[1];
		if (ms_strcmp(env_name, name) == 0)
		{
			index = i;
			break ;
		}
		i++;
		ms_split_free(split);
	}
	//ms_split_free(split);
	return (index);
}

static char
*get_variable_name(char *argv)
{
	char	**split;
	char	*name;

	split = ms_split(argv, '=');
	name = ms_strdup(split[0]);
	ms_split_free(split);
	return (name);
}

int	builtin_unset(int argc, char *argv[])
{
	extern char	**environ;
	char	*name;
	int		index;

	int		i;

	if (argc == 1)
		return (1);

	name = get_variable_name(argv[1]);
	index = get_index_of_name_in_environ(name);
	if (index >= 0)
	{
		//free(environ[index]);
		i = index;
		while (environ[i] != NULL)
		{
			environ[i] = environ[i + 1];
			i++;
		}
	}
	return (0);
}
