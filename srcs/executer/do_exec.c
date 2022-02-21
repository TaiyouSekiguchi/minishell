#include "minishell.h"

/*static t_kind
distinguish_redirect_kind(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

void	infile_redirect_part(t_list *infile)
{
	t_list	*current;
	t_kind	kind;

	current = infile;
	if (current != NULL)
	{
		kind = distinguish_redirect_kind(current->content);
		do_redirect(current->content, kind);
	}
}*/

char
**make_argv_for_execve(t_list *cmd, size_t cmd_token_count)
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

char
*cmd_path_search(char *cmd_name)
{
	char	**env_path_lst;
	int		i;
	char	*tmp;
	char	*tmp2;

	env_path_lst = ms_split(getenv("PATH"), ':');
	if (env_path_lst == NULL)
		return (NULL);
	i = 0;
	while (env_path_lst[i] != NULL)
	{
		tmp = ms_strjoin(env_path_lst[i], "/");
		tmp2 = ms_strjoin(tmp, cmd_name);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			ms_split_free(env_path_lst);
			return (tmp2);
		}
		i++;
	}
	ms_split_free(env_path_lst);
	free(tmp);
	free(tmp2);
	return (NULL);
}

void
do_exec(t_cmd *cmd_group, t_dir *d_info)
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
		do_builtin(argv[0], cmd_token_count, argv, d_info);
		return ;
	}
	else if (ms_strchr(argv[0], '/') == NULL)
	{
		//$PATHから探す
		argv[0] = cmd_path_search(argv[0]);
	}
	else
	{
		//absolute_PATHから探す　
		if (access(argv[0], X_OK) != 0)
			argv[0] = NULL;
	}
	if (argv[0] == NULL)
		ms_error("minishell command not found");
	if (execve(argv[0], argv, environ) < 0)
	{
		ms_putendl_fd(argv[0], STDERR_FILENO);
		perror("execve");
		ms_error("execve failed");
	}
}
