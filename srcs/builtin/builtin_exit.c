
#include "minishell.h"

int	builtin_exit(int argc, char *argv[])
{
	int	ret;
	char	*msg;

	ms_putendl_fd("exit", STDERR);
	if (argc >= 2)
	{
		errno = 0;
		ret = ms_atoi(argv[1]);
		if (errno == 22 || errno == 34)
		{
			set_g_status(255);
			msg = ms_strappend(ms_strdup(""), ms_strdup("exit: "));
			msg = ms_strappend(msg, ms_strdup(argv[1]));
			msg = ms_strappend(msg, ms_strdup(": numeric argment required"));
			put_error_exit("exit", get_g_status(), msg, TRUE);
		}
		if (argc > 2)
		{
			put_error_exit("exit", get_g_status(), "exit: too many arguments", FALSE);
			return (1);
		}
		set_g_status(ret);
		exit(get_g_status());
	}
	else
	{
		exit(get_g_status());
	}
	return (0);
}
