#include "minishell.h"

static void	expand_to_lst(t_list **new_lst, char *value, char **ret)
{
	t_list	*token_lst;
	t_list	*current;

	token_lst = split_lst(value, ' ');
	free(value);
	current = token_lst;
	while (current != NULL)
	{
		*ret = ms_strappend(*ret, ms_strdup(current->content));
		ms_lstadd_back(new_lst, ms_lstnew(*ret));
		*ret = ms_strdup("");
		current = current->next;
	}
	ms_lstclear(&token_lst, free);
}

static t_list	*expand_part(char **token, char **ret, char **start, char **my_env)
{
	t_list *new_lst;
	char	*value;

	new_lst = NULL;
	*ret = ms_strappend(*ret, ms_strndup(*start, *token - *start));
	*token += 1;
	if (**token == '?')
		*ret = ms_strappend(*ret, expand_g_status(token));
	else if (ms_isdigit(**token))
		*ret = ms_strappend(*ret, expand_num(token));
	else
	{
		value = expand_from_env(token, my_env);
		expand_to_lst(&new_lst, value, ret);
	}
	*start = *token;
	return (new_lst);
}

static void	expand_init(t_list **new_lst, t_quote *quote, char **ret)
{
	*new_lst = NULL;
	*quote = NONE;
	*ret = ms_strdup("");
}

static void	quote_part(char **token, t_quote *quote)
{
	*quote = quote_set(**token, *quote);
	*token += 1;
}

t_list	*expand(char *token, char **my_env)
{
	t_list	*new_lst;
	t_quote	quote;
	char	*ret;
	char	*start;

	expand_init(&new_lst, &quote, &ret);
	start = token;
	while (*token != '\0')
	{
		if (is_quote(*token))
			quote_part(&token, &quote);
		else if ((quote == SINGLE || *token != '$')
				|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
			ms_lstadd_back(&new_lst, expand_part(&token, &ret, &start, my_env));
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	if (ms_strlen(ret) != 0)
		ms_lstadd_back(&new_lst, ms_lstnew(ret));
	else
		free(ret);
	return (new_lst);
}
