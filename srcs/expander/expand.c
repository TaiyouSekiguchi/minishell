#include "minishell.h"

t_list	*split_to_lst(char **split)
{
	t_list	*new_lst;
	char	*tmp;
	int		i;

	new_lst = NULL;
	i = 0;
	while (split[i] != NULL)
	{
		tmp = ms_strdup(split[i]);
		ms_lstadd_back(&new_lst, ms_lstnew(tmp));
		i++;
	}
	return (new_lst);
}

t_list	*expand(char *token, char **my_env)
{
	t_list	*new_lst;
	t_list	*lst_last;
	t_list	*split_lst;
	t_quote	quote;
	int		start;
	int		i;
	char	*tmp;
	char	**split;
	char	*value;
	char	*val_name;

	new_lst = ms_lstnew(ms_strdup(""));
	lst_last = new_lst;
	i = 0;
	start = 0;
	quote = NONE;
	while (token[i] != '\0')
	{
		if (is_quote(token[i]))
		{
			quote = quote_set(token[i], quote);
			i++;
		}
		else if ((quote == SINGLE || token[i] != '$')
			|| (token[i + 1] != '?' && !is_name(token[i + 1])))
		{
			i++;
		}
		else
		{
			tmp = ms_substr(token, start, i - start);
			lst_last->content = ms_strappend(lst_last->content, tmp);
			i++;

			if (token[i] == '?')
			{
				lst_last->content = ms_strappend(lst_last->content, ms_itoa(get_g_status()));
				i++;
			}
			else if (ms_isdigit(token[i]))
			{
				lst_last->content = ms_strappend(lst_last->content, ms_strdup(""));
				i++;
			}
			else
			{
				val_name = get_val_name(&token[i]);
				value = ms_getenv(my_env, val_name);
				free(val_name);

				while (token[i] != '\0' && is_name(token[i]))
					i++;
				start = i;

				if (value != NULL && value[0] != '\0')
				{
					split = ms_split(value, ' ');
					lst_last->content = ms_strappend(lst_last->content, ms_strdup(split[0]));
					split_lst = split_to_lst(split);
					ms_lstadd_back(&new_lst, split_lst->next);
					ms_lstdelone(split_lst, free);
					lst_last = ms_lstlast(new_lst);
					ms_split_free(split);
				}
				free(value);
			}
		}
	}
	lst_last->content = ms_strappend(lst_last->content, ms_substr(token, start, i - start));
	return (new_lst);
}
