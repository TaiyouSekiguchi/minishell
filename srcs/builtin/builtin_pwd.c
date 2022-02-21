
#include "minishell.h"

void	builtin_pwd(int	act)
{
	static char		*pwd;

	if (act == 1)
	{
		if (pwd != NULL)
		{
			free(pwd);
			pwd = NULL;
		}
		pwd = getenv("PWD");
		if (pwd == NULL)
			ms_error("pwd");
	}
	else if (act == 2)
	{
		ms_putendl_fd(pwd, STDOUT);
	}
}
