#include "minishell.h"

extern int g_status;

int	redirect_file_open(char *token, int stdin_save)
{
	int		fd;

	if (token[0] == '<' && token[1] == ' ')
		fd = infile_open(token);
	else if (token[0] == '<' && token[1] == '<')
		fd = heredoc_open(token, stdin_save);
	else if (token[0] == '>' && token[1] == ' ')
		fd = outfile_open(token);
	else
		fd = append_open(token);

	return (fd);
}

int	get_redirect_fd(t_list *token_list, int stdin_save)
{
	int		fd;
	char	*token;

	fd = NONE_FD;
	token = NULL;
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token != NULL)
			fd = redirect_file_open(token, stdin_save);
		else
			fd = NONE_FD;
		token_list = token_list->next;
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
