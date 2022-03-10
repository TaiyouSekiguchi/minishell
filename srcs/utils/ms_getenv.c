#include "minishell.h"

char	*ms_getenv(char **my_env, char *key)
{
	char	**split;
	char	*value;
	int		i;

	i = 0;
	while (my_env[i] != NULL)
	{
		split = ms_split(my_env[i], '=');
		if (ms_strcmp(split[0], key) == 0)
		{
			value = ms_strdup(split[1]);
			ms_split_free(split);
			return (value);
		}
		ms_split_free(split);
		i++;
	}
	return (NULL);
}
