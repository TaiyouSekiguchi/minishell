#include "minishell.h"

int	builtin_pwd(t_dir *d_info)
{
	ms_putendl_fd(d_info->pwd, STDOUT);
	return (EXIT_SUCCESS);
}
