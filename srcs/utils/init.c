#include "minishell.h"

void	init_shlvl(char ***my_env)
{
	char		*env_shlvl;
	t_boolean	is_minus;
	int			num;
	char		*str_num;
	char		*save;

	if (getenv("SHLVL") == NULL)
		call_export("SHLVL", "1", my_env);
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
				call_export("SHLVL", str_num, my_env);
				free(str_num);
			}
			else
				call_export("SHLVL", "1", my_env);
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
				call_export("SHLVL", "1", my_env);
			}
			else if (is_minus == TRUE)
				call_export("SHLVL", "0", my_env);
			else
			{
				num = ms_atoi(env_shlvl) + 1;
				str_num = ms_itoa(num);
				call_export("SHLVL", str_num, my_env);
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

static int		get_environ_row(char **environ)
{
	int	row;

	row = 0;
	while (environ[row] != NULL)
		row++;
	return (row);
}

void	init_my_env(t_dir *d_info)
{
	extern char	**environ;
	int			environ_row;
	int			i;
	
	environ_row = get_environ_row(environ);
	d_info->my_env = (char **)ms_xmalloc(sizeof(char *) * (environ_row + 1));

	i = 0;
	while (i < environ_row)
	{
		d_info->my_env[i] = ms_strdup(environ[i]);
		i++;
	}
	d_info->my_env[i] = NULL;
}
