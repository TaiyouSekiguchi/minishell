/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:14:26 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/20 14:55:43 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*search(char *val_name)
{
	extern char		**environ;
	int				row;
	char			**split;
	char			*left;
	char			*right;

	printf("val_name is %s\n", val_name);
	row = 0;
	while (environ[row] != NULL)
	{
		split = ft_split(environ[row], '=');
		left = split[0];
		right = split[1];
		printf("left  is %s\n", left);
		printf("right is %s\n", right);
		if (ft_strcmp(left, &val_name[1]) == 0)
			return (right);
		row++;
	}
	return (NULL);
}

int	is_name(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

int	get_val_len(char *token)
{
	int	len;
	int	i;

	i = 0;
	while (token[i] != '\0' && token[i] != '$')
		i++;
	if (token[i] == '\0')
		return (-1);
	len = 0;
	while (token[i] != '\0' && is_name(token[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_val_name(char *token)
{
	char	*val_name;
	int		i;

	i = 1;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	val_name = ft_strndup(token, i);
	return (val_name);
}

char	*expand(char *token)
{
	char	*val_name;
	char	*new_word;
	char	*ret;
	char	*tmp;
	int		start;
	int		i;

	start = 0;
	i = 0;
	ret = "";
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			tmp = ft_substr(token, start, i - start);
			printf("tmp is %s\n", tmp);
			ret = ft_strjoin(ret, tmp);
			printf("ret is %s\n", ret);
			val_name = get_val_name(&token[i]);
			printf("val_name is %s\n", val_name);
			new_word = search(val_name);
			printf("new_word is %s\n", new_word);
			ret = ft_strjoin(ret, new_word);
			printf("ret is %s\n", ret);
			i++;
			while (token[i] != '\0' && is_name(token[i]))
			{
				i++;
			}
			start = i;
		}
		else
			i++;
	}
	tmp = ft_substr(token, start, i);
	printf("tmp is %s\n", tmp);
	ret = ft_strjoin(ret, tmp);
	printf("ret is %s\n", ret);
	return (ret);
}

void	sorezore(t_list *list)
{
	t_list	*current;

	current = list;
	while (current != NULL)
	{
		current->content = expand(current->content);
		current = current->next;
	}
}

void	do_expand(t_cmd *cmd)
{
	sorezore(cmd->cmd);
	sorezore(cmd->infile);
	sorezore(cmd->outfile);
}

void	expander(t_list *cmds)
{
	t_list	*current;

	current = cmds;
	while (current != NULL)
	{
		do_expand(current->content);
		current = current->next;
	}
}
