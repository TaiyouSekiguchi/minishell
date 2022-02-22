
#include "minishell.h"

void	builtin_pwd(t_dir *d_info)
{
	ms_putendl_fd(d_info->pwd, STDOUT);
}
//void	builtin_pwd(t_dir *d_info)
//{
//	static char		*pwd;
//
//	if (act == 1)
//	{
//		if (pwd != NULL)
//		{
//			free(pwd);
//			pwd = NULL;
//		}
//		pwd = getenv("PWD");
//		if (pwd == NULL)
//			ms_error("pwd");
//	}
//	else if (act == 2)
//	{
//		ms_putendl_fd(pwd, STDOUT);
//	}
//}