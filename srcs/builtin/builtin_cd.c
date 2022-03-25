#include "minishell.h"

static char	*set_input_path(int argc, char **argv, char **my_env)
{
	char	*value;

	if (argc == 1 || argv[1][0] == '~')
	{
		value = ms_getenv(my_env, "HOME");
		if (value == NULL)
		{
			ms_putendl_fd("minishell: cd: HOME not set", STDERR);
			return (NULL);
		}
		else if (argc == 1 || ms_strlen(argv[1]) == 1)
			return (value);
		else
			return (ms_strjoin(value, argv[1] + 1));
	}
	else
		return (ms_strdup(argv[1]));
}

char	*rewrite_path(char *input_path, t_dir *d_info)
{
	char	*new_pwd;
	t_list	*dir_lst;

	dir_lst = split_lst(input_path, '/');
	if (input_path[0] == '/')
		new_pwd = rewrite_absolute_path(dir_lst, input_path);
	else
		new_pwd = rewrite_relative_path(dir_lst, d_info->pwd);
	return (new_pwd);
}

void	update_pwd(t_dir *d_info, char *new_pwd)
{
	if (d_info->old_pwd != NULL)
		free(d_info->old_pwd);
	d_info->old_pwd = ms_strdup(d_info->pwd);
	free(d_info->pwd);
	if (ms_strncmp(new_pwd, "///", 3) == 0)
		d_info->pwd = ms_strdup("/");
	else
		d_info->pwd = ms_strdup(new_pwd);
	call_export("PWD", d_info->pwd, &d_info->my_env);
	call_export("OLDPWD", d_info->old_pwd, &d_info->my_env);
}

int	builtin_cd(int argc, char *argv[], t_dir *d_info)
{
	char		*input_path;
	char		*new_pwd;

	input_path = set_input_path(argc, argv, d_info->my_env);
	if (input_path == NULL)
		return (EXIT_FAILURE);
	else
	{
		new_pwd = rewrite_path(input_path, d_info);
		free(input_path);
		if (chdir(new_pwd) < 0)
		{
			ms_putstr_fd("minishell: cd: ", STDERR);
			perror(argv[1]);
			free(new_pwd);
			return (EXIT_FAILURE);
		}
		else
			update_pwd(d_info, new_pwd);
	}
	free(new_pwd);
	return (EXIT_SUCCESS);
}
