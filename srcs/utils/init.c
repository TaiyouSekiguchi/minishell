#include "minishell.h"

void	init_shlvl(void)
{
	char		*env_shlvl;
	t_boolean	is_minus;
	int			num;
	char		*str_num;
	char		*save;

	if (getenv("SHLVL") == NULL)
		call_export("SHLVL", "1");
	else
	{
		env_shlvl = ms_strdup(getenv("SHLVL"));
		save = env_shlvl;
		if (ms_strlen(env_shlvl) == 1)
		{
			if (*env_shlvl >= '0' && *env_shlvl <= '9')
			{
				num = ms_atoi(env_shlvl) + 1;
				str_num = ms_itoa(num);
				call_export("SHLVL", str_num);
				free(str_num);
			}
			else
				call_export("SHLVL", "1");
		}
		else
		{
			if (*env_shlvl == '+' || *env_shlvl == '-')
			{
				if (*env_shlvl == '-')
					is_minus = TRUE;
				else
					is_minus = FALSE;
				env_shlvl++;
			}
			if (ms_isnum_string(env_shlvl) == FALSE)
			{
				call_export("SHLVL", "1");
			}
			else if (is_minus == TRUE)
				call_export("SHLVL", "0");
			else
			{
				num = ms_atoi(env_shlvl) + 1;
				str_num = ms_itoa(num);
				call_export("SHLVL", str_num);
				free(str_num);
			}
		}
		free(save);
	}
}

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
