#include "minishell.h"

int	redirect_file_open(char *file_name)
{
	int		fd;

	if (file_name[0] == '<' && file_name[1] == ' ')
		fd = infile_open(file_name);
	else if (file_name[0] == '<' && file_name[1] == '<')
		fd = heredoc_open(file_name);
	else if (file_name[0] == '>' && file_name[1] == ' ')
		fd = outfile_open(file_name);
	else if (file_name[0] == '>' && file_name[1] == '>')
		fd = append_open(file_name);
	else
		fd = ERROR_FD;

	return (fd);
}

int	get_redirect_fd(t_list *file_list)
{
	int		fd;
	char	*file_name;

	if (file_list == NULL)
		return (NONE_FD);

	file_name = NULL;
	while (file_list != NULL)
	{
		file_name = file_list->content;
		fd = redirect_file_open(file_name);
		if (fd == ERROR_FD)
			break ;
		file_list = file_list->next;
	}

	return (fd);
}

void	do_redirect(int infile_fd, int outfile_fd)
{
	if (infile_fd != NONE_FD)
	{
		close(STDIN);
		dup2(infile_fd, STDIN);
		close(infile_fd);
	}
	if (outfile_fd != NONE_FD)
	{
		close(STDOUT);
		dup2(outfile_fd, STDOUT);
		close(outfile_fd);
	}
}
