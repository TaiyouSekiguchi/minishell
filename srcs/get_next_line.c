/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:31:37 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/12/13 09:00:46 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	save_check(char **line, char **save)
{
	char	*tmp;
	char	*restart;

	if (line == NULL || save == NULL)
		return (ERROR);
	*line = my_strdup(*save, '\n');
	if (*line == NULL)
		return (ERROR);
	restart = my_strchr(*save, '\n') + 1;
	tmp = my_strdup(restart, '\0');
	if (tmp == NULL)
	{
		free(*line);
		return (ERROR);
	}
	free(*save);
	*save = tmp;
	return (READ);
}

static int	save_init(char **save)
{
	if (*save != NULL)
		return (1);
	else
	{
		*save = (char *)malloc(sizeof(char));
		if (*save == NULL)
			return (0);
		*save[0] = '\0';
	}
	return (1);
}

static int	my_free(char **line)
{
	free(*line);
	return (ERROR);
}

static int	my_buffering(int fd, char **line, char **save, char *buf)
{
	int		read_byte;

	read_byte = read(fd, buf, BUFFER_SIZE);
	while (read_byte > 0)
	{
		buf[read_byte] = '\0';
		if (my_strchr(buf, '\n') == NULL)
		{
			*save = my_strjoin(*save, buf, '\0');
			if (save == NULL)
				return (ERROR);
		}
		else
		{
			*line = my_strjoin(*save, buf, '\n');
			if (*line == NULL)
				return (ERROR);
			*save = my_strdup(my_strchr(buf, '\n') + 1, '\0');
			if (*save == NULL)
				return (my_free(line));
			break ;
		}
		read_byte = read(fd, buf, BUFFER_SIZE);
	}
	return (read_byte);
}

int	get_next_line(int fd, char **line)
{
	static char		*save;
	char			*buf;
	int				ret;

	if (fd <= -1 || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	*line = NULL;
	if (my_strchr(save, '\n') != NULL)
		return (save_check(line, &save));
	if (!save_init(&save))
		return (ERROR);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (ERROR);
	ret = my_buffering(fd, line, &save, buf);
	free(buf);
	if (ret > 0)
		ret = READ;
	if (ret == 0)
	{
		*line = my_strdup(save, '\0');
		free (save);
		save = NULL;
	}
	return (ret);
}
