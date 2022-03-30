/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/25 23:43:05 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"
#include <stdio.h>

static size_t	get_line_count(char const *s, char c)
{
	int		flag;
	size_t	line_count;
	size_t	i;

	flag = 0;
	line_count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (flag == 0 && s[i] != c)
		{
			flag = 1;
			line_count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (line_count);
}

static char	**my_free(char **ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
	{
		ms_free(ret[i]);
		i++;
	}
	ms_free(ret);
	return (NULL);
}

static char	**do_split(char const *s, char c, char **ret, long line_count)
{
	long	start;
	size_t	i;

	start = -1;
	i = 0;
	while (s[i] != '\0' && ret != NULL)
	{
		if (start == -1 && s[i] != c)
			start = i;
		else if (start != -1 && s[i] == c)
		{
			ret[line_count++] = ms_substr(s, start, i - start);
			if (ret[line_count - 1] == NULL)
				ret = my_free(ret);
			start = -1;
		}
		if (start != -1 && s[i + 1] == '\0')
		{
			ret[line_count++] = ms_substr(s, start, i + 1 - start);
			if (ret[line_count - 1] == NULL)
				ret = my_free(ret);
		}
		i++;
	}
	return (ret);
}

char	**ms_split(char const *s, char c)
{
	char	**ret;
	size_t	line_count;

	if (s == NULL)
		return (NULL);
	line_count = get_line_count(s, c);
	ret = (char **)ms_xmalloc(sizeof(char *) * (line_count + 1));
	if (ret == NULL)
		return (NULL);
	ret = do_split(s, c, ret, 0);
	if (ret != NULL)
		ret[line_count] = NULL;
	return (ret);
}
