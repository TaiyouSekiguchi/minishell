/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:51:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/08 00:01:12 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_delimiter(char c)
{
	if (c == '|'
		|| c == '<'
		|| c == '>')
		return (TRUE);
	return (FALSE);
}

void	quote_set(char c, int *quote)
{
	if (*quote == NONE)
	{
		if (c == '\'')
			*quote = SINGLE;
		else if (c == '\"')
			*quote = DOUBLE;
	}
	else if (*quote == SINGLE)
	{
		if (c == '\'')
			*quote = NONE;
	}
	else if (*quote == DOUBLE)
	{
		if (c == '\"')
			*quote = NONE;
	}
}

void	*lexer(t_list **list, char *cmd)
{
	size_t	start;
	size_t	i;
	char	*tmp;
	int		quote;

	start = 0;
	i = 0;
	quote = NONE;
	while (cmd[i] != '\0' )
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote_set(cmd[i], &quote);
			i++;
		}
		else if ((quote == SINGLE || quote == DOUBLE)
				|| (!ft_isspace(cmd[i]) && !is_delimiter(cmd[i])))
			i++;
		else
		{
			if (i != start)
			{
				tmp = ft_substr(cmd, start, i - start);
				ft_lstadd_back(list, ft_lstnew(tmp));
			}
			if (is_delimiter(cmd[i]))
			{
				if ((cmd[i] == '<' && cmd[i + 1] == '<')
					|| (cmd[i] == '>' && cmd[i + 1] == '>'))
				{
					ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 2)));
					i++;
				}
				else
					ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 1)));
			}
			i++;
			start = i;
		}
	}

	if (quote == SINGLE || quote == DOUBLE)
	{
		printf("quote is not close\n");
		exit(1);
	}
	if (start < i)
	{
		tmp = ft_substr(cmd, start, i - start);
		ft_lstadd_back(list, ft_lstnew(tmp));
	}
	return (list);
}



void	test(char *str)
{
	t_list	*list;
	t_list	*current;
	size_t	i;

	printf("***********test************\n");
	printf("test str is %s!!\n", str);
	list = NULL;
	lexer(&list, str);
	
	i = 0;
	current = list;
	while (current != NULL)
	{
		printf("list[%zu] is %s\n", i, (char *)current->content);
		i++;
		current = current->next;
	}
	ft_lstclear(&list, free);
	printf("***********test************\n");
}

int main(void)
{
	test("");
	test("aaa");
	test("aaa   ");
	test("aaa bbb ccc      ");
	test("    aaa bbb ccc    ");
	test("echo taiyou");
	test("echo \"taiyou\"sekiguchi");
	test("echo \"taiyou\" sekiguchi");
	test("echo \"ta\"i\"you\"sekiguchi");
	test("echo taiyou>file");
	test("echo \"taiyou>file\"");
	test("echo \"taiy\'ou>file\"");
	test("aaa ; bbb|<");
	test("echo >> taiyou");
	test("echo > > taiyou");
	test("echo 'sekiguchi taiyou'");
	test("echo \"sekiguchi taiyou\"");
	test("echo \"hello w\"'orld'; cat<file|wc");
	test("");
//	system("leaks minishell");
	return (0);
}
