#include "minishell.h"

void	init_dir_info(t_dir *d_info)
{
	struct stat	env_buf;
	struct stat	now_buf;
	char		*env_pwd;

	stat(".", &now_buf);
	if (getenv("PWD") != NULL)
	{
		env_pwd = ms_strdup(getenv("PWD"));
		stat(env_pwd, &env_buf);
		if (now_buf.st_ino == env_buf.st_ino)
		{
			d_info->pwd = env_pwd;
		}
		else
		{
			d_info->pwd = getcwd(NULL, 0);
			free(env_pwd);
		}
	}
	else
	{
		d_info->pwd = getcwd(NULL, 0);
	}
	d_info->old_pwd = NULL;
}
