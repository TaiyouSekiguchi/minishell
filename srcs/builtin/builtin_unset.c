
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

int	is_key_validate(char *key)
{
	if (*key != '_' && ms_isalpha(*key) == FALSE)
		return (FALSE);
	key++;
	while (*key != '\0')
	{
		if (is_name(*key) == FALSE)
			return (FALSE);
		key++;
	}
	return (TRUE);
}

int	unset_key(char *key, char ***environ)
{
	int		index;
	int		i;
	char	*tmp;

	if (is_key_validate(key) != TRUE)
	{
		tmp = ms_strappend(ms_strdup("`"), ms_strdup(key));
		tmp = ms_strappend(tmp, ms_strdup("\'"));
		tmp = ms_strappend(tmp, ms_strdup(": not a valid identifier"));
		put_error_exit("unset", tmp, FALSE);
		free(tmp);
		return (EXIT_FAILURE);
	}
	index = get_index_of_key(key, *environ);
	if (index != -1)
	{
		free((*environ)[index]);
		i = index;
		while ((*environ)[i] != NULL)
		{
			(*environ)[i] = (*environ)[i + 1];
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(int argc, char *argv[], char ***environ)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	if (argc == 1)
		return (ret);
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			if(unset_key(argv[i], environ) == EXIT_FAILURE)
				ret = EXIT_FAILURE;
			i++;
		}
	}
	return (ret);
}
