#include "minishell.h"

static char	**make_argv(t_list *cmd, int argc)
{
	char	**argv;
	t_list	*current;
	size_t	i;

	argv = (char **)ms_xmalloc(sizeof(char *) * (argc + 1));
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

static void	env_path_part(char **argv, char **my_env)
{
	argv[0] = cmd_path_search(argv[0], my_env);
	if (argv[0] == NULL)
		exit(get_g_status());
}

static void	direct_path_part(char **argv)
{
	struct stat	buf;

	if (access(argv[0], F_OK) != 0)
	{
		set_g_status(COMMAND_NOT_FOUND);
		put_error_exit(argv[0], NULL, TRUE);
	}
	if (access(argv[0], X_OK) != 0)
	{
		set_g_status(PERMISSION_DENIED);
		put_error_exit(argv[0], NULL, TRUE);
	}
	stat(argv[0], &buf);
	if (S_ISDIR(buf.st_mode))
	{
		set_g_status(PERMISSION_DENIED);
		put_error_exit(argv[0], " is a directory", TRUE);
	}
}

void	do_exec(t_cmd_info *cmd_group, t_dir *d_info)
{
	int		argc;
	char	**argv;

	argc = ms_lstsize(cmd_group->cmd);
	argv = make_argv(cmd_group->cmd, argc);
	if (is_builtin(argv[0]))
	{
		set_g_status(do_builtin(argv[0], argc, argv, d_info));
		ms_split_free(argv);
		return ;
	}
	else if (ms_strcmp(argv[0], ".") == 0)
	{
		set_g_status(2);
		put_error_exit(argv[0], " filename argument required", FALSE);
		ms_putendl_fd(".: usage: . filename [arguments]", STDERR);
		exit(get_g_status());
	}
	else if (ms_strchr(argv[0], '/') == NULL)
		env_path_part(argv, d_info->my_env);
	else
		direct_path_part(argv);
	if (execve(argv[0], argv, d_info->my_env) < 0)
	{
		put_error_exit(argv[0], NULL, FALSE);
		ms_split_free(argv);
		set_g_status(126);
		exit(get_g_status());
	}
}
