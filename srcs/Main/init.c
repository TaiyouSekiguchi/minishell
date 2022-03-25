#include "minishell.h"

static void	shlvl_increment(char *env_shlvl, char ***my_env)
{
	int		num;
	char	*str_num;

	num = ms_atoi(env_shlvl) + 1;
	str_num = ms_itoa(num);
	call_export("SHLVL", str_num, my_env);
	ms_free(str_num);
}

void	update_shlvl(char ***my_env, char *tmp)
{
	t_boolean	is_minus;

	is_minus = FALSE;
	if (*tmp == '+' || *tmp == '-')
	{
		if (*tmp == '-')
			is_minus = TRUE;
		tmp++;
	}
	if (ms_isnum_string(tmp) == FALSE)
		call_export("SHLVL", "1", my_env);
	else if (is_minus == TRUE)
		call_export("SHLVL", "0", my_env);
	else
		shlvl_increment(tmp, my_env);
}

void	init_shlvl(char ***my_env)
{
	char		*env_shlvl;
	char		*tmp;

	env_shlvl = ms_getenv(*my_env, "SHLVL");
	if (env_shlvl == NULL)
		call_export("SHLVL", "1", my_env);
	else
	{
		tmp = env_shlvl;
		if (ms_strlen(tmp) == 1)
		{
			if (ms_isdigit(*tmp))
				shlvl_increment(tmp, my_env);
			else
				call_export("SHLVL", "1", my_env);
		}
		else
			update_shlvl(my_env, tmp);
	}
	ms_free(env_shlvl);
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
			ms_free(env_pwd);
		}
	}
	else
		d_info->pwd = getcwd(NULL, 0);
	d_info->old_pwd = NULL;
}

void	init(t_dir *d_info)
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
	init_dir_info(d_info);
	init_shlvl(&(d_info->my_env));
}
