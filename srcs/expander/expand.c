#include "minishell.h"

char	*get_val_name(char *token)
{
	char	*val_name;
	int		i;

	i = 0;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	val_name = ms_strndup(token, i);
	return (val_name);
}

char	*expand_for_heredoc(char *token, char **my_env)
{
	char	*value;
	char	*ret;
	char	*start;
	char	*val_name;

	ret = ms_strdup("");
	start = token;
	while (*token != '\0')
	{
		if ((*token != '$')
			|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
		{
			ret = ms_strappend(ret, ms_strndup(start, token - start));
			token++;
			if (*token == '?')
			{
				value = ms_itoa(get_g_status());
				token++;
			}
			else if (ms_isdigit(*token))
			{
				value = ms_strdup("");
				token++;
			}
			else
			{
				val_name = get_val_name(token);
				value = ms_getenv(my_env, val_name);
				free(val_name);
				if (value == NULL)
					value = ms_strdup("");

				while (*token != '\0' && is_name(*token))
					token++;
			}
			ret = ms_strappend(ret, value);
			start = token;
		}
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	return (ret);
}

t_list	*expand(char *token, t_boolean in_heredoc, char **my_env)
{
	char	*value;
	char	*ret;
	t_quote	quote;
	char	*start;
	char	*val_name;
	t_list	*new_lst;
	t_list	*token_lst;
	t_list	*current;

	new_lst = NULL;
	quote = NONE;
	ret = ms_strdup("");
	start = token;
	while (*token != '\0')
	{
		if (in_heredoc == FALSE && is_quote(*token))
		{
			quote = quote_set(*token, quote);
			token++;
		}
		else if ((quote == SINGLE || *token != '$')
				|| (*(token + 1) != '?' && !is_name(*(token + 1))))
			token++;
		else
		{
			ret = ms_strappend(ret, ms_strndup(start, token - start));
			token++;
			if (*token == '?')
			{
				value = ms_itoa(get_g_status());
				ret = ms_strappend(ret, value);
				token++;
			}
			else if (ms_isdigit(*token))
			{
				value = ms_strdup("");
				ret = ms_strappend(ret, value);
				token++;
			}
			else
			{
				val_name = get_val_name(token);
				value = ms_getenv(my_env, val_name);
				free(val_name);
				if (value == NULL)
					value = ms_strdup("");
				token_lst = split_lst(value, ' ');
				free(value);
				current = token_lst;
				while (current != NULL)
				{
					ret = ms_strappend(ret, ms_strdup(current->content));
					ms_lstadd_back(&new_lst, ms_lstnew(ret));
					ret = ms_strdup("");
					current = current->next;
				}
				ms_lstclear(&token_lst, free);
				while (*token != '\0' && is_name(*token))
					token++;
			}
			start = token;
		}
	}
	ret = ms_strappend(ret, ms_strndup(start, token - start));
	if (ms_strlen(ret) != 0)
		ms_lstadd_back(&new_lst, ms_lstnew(ret));
	else
		free(ret);
	return (new_lst);
}
