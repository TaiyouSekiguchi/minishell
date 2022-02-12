/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:31:00 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/12/09 15:01:04 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define READ 1
# define END 0
# define ERROR -1

size_t	my_strlen(const char *s);
char	*my_strchr(const char *s, char c);
char	*my_strjoin(const char *s1, const char *s2, char c);
char	*my_strdup(const char *s, char c);
int		get_next_line(int fd, char **line);

#endif
