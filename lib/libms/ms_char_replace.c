#include "libms.h"

char	*ms_char_replace(char *str, char old, char new)
{
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == old)
			str[i] = new;
		i++;
	}
	return (str);
}
