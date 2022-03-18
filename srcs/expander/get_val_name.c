#include "minishell.h"

char	*get_val_name(char *token)
{
	int		i;

	i = 0;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	return (ms_strndup(token, i));
}
