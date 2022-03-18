#include "minishell.h"

int	get_environ_row(char **environ)
{
	int	row;

	row = 0;
	while (environ[row] != NULL)
		row++;
	return (row);
}
