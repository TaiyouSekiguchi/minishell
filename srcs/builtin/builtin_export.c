
#include "minishell.h"

static int	get_index_of_name_in_environ(char *name)
{
	extern char		**environ;
	char			**split;
	char			*env_name;
//	char			*env_value;
	int				index;
	size_t			i;

	index = -1;
	split = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ms_split(environ[i], '=');
		env_name = split[0];
	//	env_value = split[1];
		if (ms_strcmp(env_name, name) == 0)
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

static char	*get_variable_name(char *argv)
{
	char	**split;
	char	*name;

	split = ms_split(argv, '=');
	name = ms_strdup(split[0]);
	ms_split_free(split);
	return (name);
}


static int	count_environ_variable(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	return (i);
}

int	builtin_export(int argc, char *argv[])
{
	extern char	**environ;
	char		*name;
	int			index;
	int			len;
	char		**new_env;
	int			i;

	if (argc == 1)
		return (1);

	name = get_variable_name(argv[1]);
	index = get_index_of_name_in_environ(name);
	free(name);
	if (index == -1)
	{
		len = count_environ_variable();
		new_env = (char **)ms_xmalloc(sizeof(char *) * (len + 1 + 1));
		i = 0;
		while (environ[i] != NULL)
		{
			new_env[i] = environ[i];
			i++;
		}
		new_env[i] = ms_strdup(argv[1]);
		i++;
		new_env[i] = NULL;
		//free(environ)???
		environ = new_env;
	}
	else
	{
		//free(environ[index]);
		environ[index] = ms_strdup(argv[1]);
	}
	return (0);
}
