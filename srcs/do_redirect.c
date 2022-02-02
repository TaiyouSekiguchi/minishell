/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:51:03 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 15:51:46 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirect(char *tmp, t_kind kind)
{
	int		fd;
	int		fd_1;
	int		fd_2;
	int		result;
	char	*file;
	char	*line;
	char	*deli;

	if (kind == INFILE)
	{
		file = ms_strdup(&tmp[2]);
		fd = open(file, O_RDONLY);
		if (fd < 0)
			ms_error("open");
		close(0);
		dup2(fd, 0);
		close(fd);
	}
	else if (kind == HEREDOC)
	{
		deli = ms_strdup(&tmp[3]);
		fd_1 = open("./tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (fd_1 < 0)
			ms_error("open");
		
		while(1)
		{
			write(1, "heredoc > ", 10);
			result = get_next_line(0, &line);
			if (result == ERROR)
				ms_error("gnl failed");
			else if (result == END)
				break ;
			else
			{
				if (ms_strcmp(line, deli) == 0)
					break ;
				write(fd_1, line, ms_strlen(line));
				write(fd_1, "\n", 1);
			}
		}
		close(fd_1);

		fd_2 = open("./tmp", O_RDONLY);
		if (fd_2 < 0)
			ms_error("open failed");

		unlink("./tmp");

		close(0);
		if (dup2(fd_2, 0) < 0)
			ms_error("dup2 failed");
		close(fd_2);
	}
}
