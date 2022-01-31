/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:32:16 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/12/09 14:24:46 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*my_strchr(const char *s, char c)
{
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	count = my_strlen(s);
	i = 0;
	while (i <= count)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*my_strjoin(const char *s1, const char *s2, char c)
{
	char	*ret;
	char	*copy_ret;
	char	*copy_s1;
	char	*copy_s2;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (my_strchr(s2, c) != NULL)
		len = my_strlen(s1) + (my_strchr(s2, c) - s2);
	else
		len = my_strlen(s1) + my_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	copy_ret = ret;
	copy_s1 = (char *)s1;
	copy_s2 = (char *)s2;
	while (*copy_s1 != '\0')
		*copy_ret++ = *copy_s1++;
	while (*copy_s2 != c && *copy_s2 != '\0')
		*copy_ret++ = *copy_s2++;
	*copy_ret = '\0';
	free((char *)s1);
	return (ret);
}

char	*my_strdup(const char *s, char c)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (my_strchr(s, c) != NULL)
		len = my_strchr(s, c) - s;
	else
		len = my_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
