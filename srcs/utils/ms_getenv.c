#include "minishell.h"

char	*ms_getenv(char **my_env, char *key)
{
	char	*env_key;
	char	*env_value;
	char	*pos;
	int		i;

	i = 0;
	while (my_env[i] != NULL)
	{
		pos = ms_strchr(my_env[i], '=');
		if (pos != NULL)
		{
			env_key = ms_strndup(my_env[i], pos - my_env[i]);
			if (ms_strcmp(env_key, key) == 0)
			{
				ms_free(env_key);
				pos++;
				env_value = ms_strdup(pos);
				return (env_value);
			}
			ms_free(env_key);
		}
		i++;
	}
	return (NULL);
}
