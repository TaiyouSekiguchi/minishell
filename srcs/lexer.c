/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:51:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/06 22:13:04 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (str == NULL || n == 0)
		return (NULL);
	len = ft_strlen(str);
	if (len > n)
		len = n;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	is_space(char c)
{
	if (c == ' ')
		return (TRUE);
	return (FALSE);
}

int	is_delimiter(char c)
{
	if (c == '|'
		|| c == ';'
		|| c == '<'
		|| c == '>')
		return (TRUE);
	return (FALSE);
}

int	is_quote(int *s, int *d, char c)
{
	if (*s == OUT && *d == OUT)
	{
		if (c == '\'')
			*s = IN;
		else if (c == '\"')
			*s = IN;
	}
	else if (*s == IN && *d == OUT)
	{
		if (c == '\'')
			*s = OUT;
	}
	else if (*s == OUT && *d == IN)
	{
		if (c == '\"')
			*d = OUT;
	}
	return (0);
}

void	*lexer(t_list **list, char *cmd)
{
	size_t	start;
	size_t	i;
	char	*tmp;
	int		flag;

	start = 0;
	i = 0;
	flag = 0;
	while (cmd[i] != '\0' )
	{
		if (!is_space(cmd[i]) && !is_delimiter(cmd[i]))
		{
			flag = 1;
			i++;
		}
		else if (is_space(cmd[i]) && flag == 1)
		{
			tmp = ft_substr(cmd, start, i - start);
			//printf("tmp is %s\n", tmp);
			ft_lstadd_back(list, ft_lstnew(tmp));
			i++;
			start = i;
			flag = 0;
		}
		else if (is_space(cmd[i]) && flag == 0)
		{
			i++;
			start = i;
		}
		else if (is_delimiter(cmd[i]) && flag == 1)
		{
			tmp = ft_substr(cmd, start, i - start);
			//printf("tmp is %s\n", tmp);
			ft_lstadd_back(list, ft_lstnew(tmp));
			if ((cmd[i] == '<' && cmd[i + 1] == '<')
				|| (cmd[i] == '>' && cmd[i + 1] == '>'))
			{
				ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 2)));
				i++;
			}
			else
				ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 1)));
			i++;
			start = i;
			flag = 0;
		}
		else if (is_delimiter(cmd[i]) && flag == 0)
		{
			if ((cmd[i] == '<' && cmd[i + 1] == '<')
				|| (cmd[i] == '>' && cmd[i + 1] == '>'))
			{
				ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 2)));
				i++;
			}
			else
				ft_lstadd_back(list, ft_lstnew(ft_strndup(&cmd[i], 1)));
			i++;
			start = i;
		}
	}
	if (start < i)
	{
		tmp = ft_substr(cmd, start, i - start);
		//printf("tmp is %s\n", tmp);
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
	printf("test str is %s\n", str);
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
	test("aaa ; bbb|<");
	test("echo >> taiyou");
	test("echo > > taiyou");
	test("");
	test("");
	test("");







	system("leaks minishell");
	return (0);
}
