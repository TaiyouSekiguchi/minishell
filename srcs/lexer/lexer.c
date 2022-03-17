#include "minishell.h"

static void	add_tokens(t_list **token_list, char *input, size_t start, size_t *i)
{
	char	*tmp;

	if (*input == '\0' || start < *i)
	{
		tmp = ms_strndup(&input[start], *i - start);
		ms_lstadd_back(token_list, ms_lstnew(tmp));
	}
	if (is_delimiter(input[*i]))
	{
		if (is_redirect(input[*i], input[*i + 1]))
		{
			ms_lstadd_back(token_list, ms_lstnew(ms_strndup(&input[*i], 2)));
			*i += 1;
		}
		else
			ms_lstadd_back(token_list, ms_lstnew(ms_strndup(&input[*i], 1)));
	}
}

static void	not_close_quote(t_list **token_list)
{
	put_error_exit(NULL, SYNTAX_ERROR_MSG, FALSE);
	ms_lstclear(token_list, free);
	*token_list = NULL;
}

void	lexer(t_list **token_list, char *input)
{
	t_quote		quote;
	size_t		start;
	size_t		i;

	*token_list = NULL;
	quote = NONE;
	start = 0;
	i = 0;
	while (input[i] != '\0' )
	{
		if (is_quote(input[i]))
			quote = quote_set(input[i++], quote);
		else if (quote != NONE || !is_metachar(input[i]))
			i++;
		else
		{
			add_tokens(token_list, input, start, &i);
			start = ++i;
		}
	}
	if (quote != NONE)
		not_close_quote(token_list);
	else
		add_tokens(token_list, input, start, &i);
}
