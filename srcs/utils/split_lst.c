#include "minishell.h"

t_list	*split_lst(char *str, char c)
{
	t_list	*lst;
	char	**dir_pptr;
	int		i;
	char	*tmp;

	dir_pptr = ms_split(str, c);
	if (dir_pptr == NULL)
		return (NULL);
	lst = NULL;
	i = 0;
	while (dir_pptr[i] != NULL)
	{
		tmp = ms_strdup(dir_pptr[i]);
		ms_lstadd_back(&lst, ms_lstnew(tmp));
		i++;
	}
	ms_split_free(dir_pptr);
	return (lst);
}
