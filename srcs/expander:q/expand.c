#include "minishell.h"

t_quote	quote_part(char **token, t_quote quote)
{
	t_quote	ret;

	ret = quote_set(**token, quote);
	*token += 1;
	return (ret);
}

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

void	standard_expand(char **token, char **my_env, t_list *new_lst)
{
	t_list	*lst_last;
	t_list	*split_lst;
	char	*value;
	char	**split;
	char	*tmp;

	lst_last = ms_lstlast(new_lst);
	value = expand_from_env(token, my_env);
	if (value != NULL && value[0] != '\0')
	{
		split = ms_split(value, ' ');
		tmp = ms_strdup(split[0]);
		lst_last->content = ms_strappend(lst_last->content, tmp);
		split_lst = split_to_lst(split);
		ms_lstadd_back(&new_lst, split_lst->next);
		ms_lstdelone(split_lst, free);
		lst_last = ms_lstlast(new_lst);
		ms_split_free(split);
	}
	free(value);
}

void	expand_part(char **token, char **start, char **my_env, t_list *new_lst)
{
	t_list	*lst_last;
	char	*tmp;

	lst_last = ms_lstlast(new_lst);
	tmp = ms_strndup(*start, *token - *start);
	lst_last->content = ms_strappend(lst_last->content, tmp);
	*token += 1;
	if (**token == '?')
	{
		tmp = expand_g_status(token);
		lst_last->content = ms_strappend(lst_last->content, tmp);
	}
	else if (ms_isdigit(**token))
	{
		tmp = expand_num(token);
		lst_last->content = ms_strappend(lst_last->content, tmp);
	}
	else
		standard_expand(token, my_env, new_lst);
	*start = *token;
}

t_list	*expand(char *token, char **my_env)
{
	t_list	*new_lst;
	t_list	*lst_last;
	t_quote	quote;
	char	*start;
	char	*tmp;

	new_lst = ms_lstnew(ms_strdup(""));
	lst_last = new_lst;
	start = token;
	quote = NONE;
	while (*token != '\0')
	{
		if (is_quote(*token))
			quote = quote_part(&token, quote);
		else if ((quote == SINGLE || *token != '$')
			|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
			expand_part(&token, &start, my_env, new_lst);
	}
	tmp = ms_strndup(start, token - start);
	lst_last->content = ms_strappend(lst_last->content, tmp);
	return (new_lst);
}
