#include "minishell.h"

static char	**get_split_env_path(char **my_env)
{
	char	**split_env_path;
	char	*env_path;

	env_path = ms_getenv(my_env, "PATH");
	if (env_path == NULL)
		return (NULL);
	split_env_path = ms_split(env_path, ':');
	free(env_path);
	return (split_env_path);
}

static char	*search_part(char *cmd, char **split_env_path)
{
	char	*full_path;
	char	*tmp;
	int		exit_status;
	int		i;

	exit_status = COMMAND_NOT_FOUND;
	i = -1;
	while (ms_strcmp(cmd, "") != 0 && split_env_path[++i] != NULL)
	{
		tmp = ms_strjoin(split_env_path[i], "/");
		full_path = ms_strappend(tmp, ms_strdup(cmd));
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				ms_split_free(split_env_path);
				return (full_path);
			}
			else
				exit_status = PERMISSION_DENIED;
		}
		free(full_path);
	}
	set_g_status(exit_status);
	return (NULL);
}

char	*cmd_path_search(char *cmd_name, char **my_env)
{
	char	**split_env_path;
	char	*full_path;

	split_env_path = get_split_env_path(my_env);
	if (split_env_path == NULL)
	{
		set_g_status(127);
		put_error_exit(cmd_name, "No such file or directory", FALSE);
		free(cmd_name);
		return (NULL);
	}
	full_path = search_part(cmd_name, split_env_path);
	if (full_path != NULL)
	{
		free(cmd_name);
		return (full_path);
	}
	if (get_g_status() == COMMAND_NOT_FOUND)
		put_error_exit(cmd_name, "command not found", FALSE);
	else
		put_error_exit(cmd_name, NULL, FALSE);
	ms_split_free(split_env_path);
	free(cmd_name);
	return (NULL);
}
