#include "minishell.h"

char	**make_argv_for_execve(t_list *cmd, size_t cmd_token_count)
{
	char	**argv;
	t_list	*current;
	size_t	i;

	argv = (char **)ms_xmalloc(sizeof(char *) * (cmd_token_count + 1));
	current = cmd;
	i = 0;
	while (current != NULL)
	{
		argv[i] = ms_strdup(current->content);
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*cmd_path_search(char *cmd_name, char **my_env)
{
	char	*env_path;
	char	**split_env_path;
	int		exit_status;
	int		i;
	char	*tmp;
	char	*full_path;

	env_path = search_environ(my_env, "PATH");
	split_env_path = ms_split(env_path, ':');
	if (split_env_path == NULL)
		return (NULL);

	exit_status = COMMAND_NOT_FOUND;
	i = 0;
	while (split_env_path[i] != NULL)
	{
		tmp = ms_strjoin(split_env_path[i], "/");
		full_path = ms_strjoin(tmp, cmd_name);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(env_path);
				ms_split_free(split_env_path);
				free(tmp);
				free(cmd_name);
				return (full_path);
			}
			else
				exit_status = PERMISSION_DENIED;
		}
		free(tmp);
		free(full_path);
		i++;
	}

	free(env_path);
	ms_split_free(split_env_path);
	free(tmp);
	free(full_path);

	set_g_status(exit_status);

	put_error_exit(cmd_name, get_g_status(), NULL, FALSE);
	free(cmd_name);

	return (NULL);
}

void	do_exec(t_cmd_info *cmd_group, t_dir *d_info)
{
	//extern char		**environ;
	char			**argv;
	size_t			cmd_token_count;

	//parse from list to array for execve
	cmd_token_count = ms_lstsize(cmd_group->cmd);
	argv = make_argv_for_execve(cmd_group->cmd, cmd_token_count);
	//exec part
	if (is_builtin(argv[0]))
	{
		set_g_status(do_builtin(argv[0], cmd_token_count, argv, d_info));
		ms_split_free(argv);
		return ;
	}
	else if (ms_strchr(argv[0], '/') == NULL)
	{
		//$PATHから探す
		argv[0] = cmd_path_search(argv[0], d_info->my_env);
		if (argv[0] == NULL)
			exit(get_g_status());
	}
	else
	{
		//relate absolute_PATHから探す
		if (access(argv[0], F_OK) != 0)
		{
			put_error_exit(argv[0], COMMAND_NOT_FOUND, NULL, TRUE);
		}
		if (access(argv[0], X_OK) != 0)
		{
			put_error_exit(argv[0], PERMISSION_DENIED, NULL, TRUE);
		}
	}
	if (execve(argv[0], argv, d_info->my_env) < 0)
	{
		ms_split_free(argv);
		put_error_exit(argv[0], get_g_status(), NULL, TRUE);
	}
}
