#include "minishell.h"

static int	g_status;

int	get_g_status(void)
{
	return (g_status);
}

void	set_g_status(long num)
{
	unsigned long	tmp;

	if (num >= 0)
	{
		tmp = num;
		if (tmp <= 255)
			g_status = tmp;
		else
			g_status = tmp % 256;
	}
	else
	{
		tmp = num * -1;
		tmp--;
		if (tmp <= 255)
			g_status = 255 - tmp;
		else
		{
			g_status = 255 - (tmp % 256);
		}
	}
}

void	set_g_status_exception(int num)
{
	g_status = num;
}
