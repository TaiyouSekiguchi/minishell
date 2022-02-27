#include "minishell.h"

int
is_builtin(char *cmd_name)
{
	if (ms_strcmp(cmd_name, "echo") == 0
		|| ms_strcmp(cmd_name, "cd") == 0
		|| ms_strcmp(cmd_name, "pwd") == 0
		|| ms_strcmp(cmd_name, "export") == 0
		|| ms_strcmp(cmd_name, "unset") == 0
		|| ms_strcmp(cmd_name, "env") == 0
		|| ms_strcmp(cmd_name, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int
do_builtin(char *cmd, int argc, char *argv[], t_dir *d_info)
{
	int	ret;

	ret = 0;
	if (ms_strcmp(cmd, "echo") == 0)
		ret = builtin_echo(argc, argv);
	else if (ms_strcmp(cmd, "cd") == 0)
		ret = builtin_cd(argc, argv, d_info);
	else if (ms_strcmp(cmd, "pwd") == 0)
		ret = builtin_pwd(d_info);
	else if (ms_strcmp(cmd, "export") == 0)
		ret = builtin_export(argc, argv);
	else if (ms_strcmp(cmd, "unset") == 0)
		ret = builtin_unset(argc, argv);
	else if (ms_strcmp(cmd, "env") == 0)
		ret = builtin_env();
	else if (ms_strcmp(cmd, "exit") == 0)
		ret = builtin_exit(argc, argv);
	else
		ret = 1;
	return (ret);
}
