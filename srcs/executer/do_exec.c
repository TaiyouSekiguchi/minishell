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
		argv[i] = current->content;
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*cmd_path_search(char *cmd_name)
{
	char	**env_path_lst;
	int		i;
	char	*tmp;
	char	*tmp2;
	int		exit_status;

	env_path_lst = ms_split(getenv("PATH"), ':');
	if (env_path_lst == NULL)
		return (NULL);
	i = 0;
	exit_status = COMMAND_NOT_FOUND;
	while (env_path_lst[i] != NULL)
	{
		tmp = ms_strjoin(env_path_lst[i], "/");
		tmp2 = ms_strjoin(tmp, cmd_name);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
			{
				free(tmp);
				ms_split_free(env_path_lst);
				return (tmp2);
			}
			else
				exit_status = PERMISSION_DENIED;
		}
		i++;
	}
	set_g_status(exit_status);
	ms_split_free(env_path_lst);
	free(tmp);
	free(tmp2);
	put_error_exit(cmd_name, get_g_status(), NULL, FALSE);
	return (NULL);
}

void
do_exec(t_cmd_info *cmd_group, t_dir *d_info)
{
	extern char		**environ;
	char			**argv;
	size_t			cmd_token_count;

	//parse from list to array for execve
	cmd_token_count = ms_lstsize(cmd_group->cmd);
	argv = make_argv_for_execve(cmd_group->cmd, cmd_token_count);
	//exec part
	if (is_builtin(argv[0]))
	{
		set_g_status(do_builtin(argv[0], cmd_token_count, argv, d_info));
		return ;
	}
	else if (ms_strchr(argv[0], '/') == NULL)
	{
		//$PATHから探す
		argv[0] = cmd_path_search(argv[0]);
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
	if (execve(argv[0], argv, environ) < 0)
	{
		put_error_exit(argv[0], get_g_status(), NULL, TRUE);
	}
}
