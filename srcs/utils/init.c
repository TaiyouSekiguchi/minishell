#include "minishell.h"

static void	shlvl_increment(char *env_shlvl, char ***my_env)
{
	int		num;
	char	*str_num;

	num = ms_atoi(env_shlvl) + 1;
	str_num = ms_itoa(num);
	call_export("SHLVL", str_num, my_env);
	free(str_num);
}

void	init_shlvl(char ***my_env)
{
	char		*env_shlvl;
	char		*save;
	t_boolean	is_minus;

	env_shlvl = ms_getenv(*my_env, "SHLVL");
	if (env_shlvl == NULL)
		call_export("SHLVL", "1", my_env);
	else
	{
		save = env_shlvl;
		if (ms_strlen(env_shlvl) == 1)
		{
			if (ms_isdigit(*env_shlvl))
				shlvl_increment(env_shlvl, my_env);
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
				call_export("SHLVL", "1", my_env);
			else if (is_minus == TRUE)
				call_export("SHLVL", "0", my_env);
			else
				shlvl_increment(env_shlvl, my_env);
		}
		free(save);
	}
}

void	init_dir_info(t_dir *d_info)
{
	struct stat	env_buf;
	struct stat	now_buf;
	char		*env_pwd;

	call_unset("OLDPWD", &(d_info->my_env));
	stat(".", &now_buf);
	if (getenv("PWD") != NULL)
	{
		env_pwd = ms_strdup(getenv("PWD"));
		stat(env_pwd, &env_buf);
		if (now_buf.st_ino == env_buf.st_ino)
			d_info->pwd = env_pwd;
		else
		{
			d_info->pwd = getcwd(NULL, 0);
			free(env_pwd);
		}
	}
	else
		d_info->pwd = getcwd(NULL, 0);
	d_info->old_pwd = NULL;
}

static int	get_environ_row(char **environ)
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
	int			row;
	int			i;
	
	row = get_environ_row(environ);
	d_info->my_env = (char **)ms_xmalloc(sizeof(char *) * (row + 1));
	i = 0;
	while (environ[i] != NULL)
	{
		d_info->my_env[i] = ms_strdup(environ[i]);
		i++;
	}
	d_info->my_env[i] = NULL;
}
