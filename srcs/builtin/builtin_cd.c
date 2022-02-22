
#include "minishell.h"

void	builtin_cd(int argc, char *argv[], t_dir *d_info)
{
	char	*home_path;
	int		ret;
	int		i;
	char	**split;
	char	*tmp;
	char	*tmp2;

	if (d_info == NULL)
		printf("d_info is NULL");

	//引数が２つ以上あたえられたときはエラー
	if (argc > 2)
		ms_error("cd failed");

	if (argc == 1)
	{
		//引数がなにもなかった場合
		home_path = ms_strdup(getenv("HOME"));
		if (ms_strcmp(home_path, "") == 0)
			ms_error("cd: HOME is empty.");
		ret = chdir(home_path);
		if (ret < 0)
		{
			ms_putendl_fd("cd failed", STDOUT);
		}
		else
		{
			if (d_info->old_pwd != NULL)
			{
				free(d_info->old_pwd);
				d_info->old_pwd = NULL;
			}
			d_info->old_pwd = d_info->pwd;
			d_info->pwd = home_path;
		}
	}
	else
	{
		//一つの引数があたえられた場合
		ret = chdir(argv[1]);
		if (ret < 0)
		{
			ms_putendl_fd("cd failed", STDOUT);
		}
		else
		{
			if (d_info->old_pwd != NULL)
			{
				free(d_info->old_pwd);
				d_info->old_pwd = NULL;
			}
			d_info->old_pwd = d_info->pwd;

			//絶対パス
			if (argv[1][0] == '/')
			{
				tmp = ms_strdup("");
				split = ms_split(argv[1], '/');
				i = 0;
				while (split[i] != NULL)
				{
					if (ms_strcmp(".", split[i]) == 0)
						;
					else if (ms_strcmp("..", split[i]) == 0)
					{
						tmp2 = tmp;
						tmp = ms_substr(tmp2, 0, ms_strrchr(tmp2, '/') - tmp2);
						free(tmp2);
					}
					else
					{
						tmp = ms_strappend(tmp, "/");
						tmp = ms_strappend(tmp, split[i]);
					}
					i++;
				}
				d_info->pwd = tmp;
			}
		}
	}
}
