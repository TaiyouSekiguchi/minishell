#include "minishell.h"

void	redirect_file_open(char *file_name, int *infile_fd, int *outfile_fd, int heredoc_fd)
{
	if (file_name[0] == '<' && file_name[1] == ' ')
		*infile_fd = infile_open(file_name);
	else if (file_name[0] == '<' && file_name[1] == '<')
		*infile_fd = heredoc_fd;
	else if (file_name[0] == '>' && file_name[1] == ' ')
		*outfile_fd = outfile_open(file_name);
	else if (file_name[0] == '>' && file_name[1] == '>')
		*outfile_fd = append_open(file_name);
	else
	{
		*infile_fd = ERROR_FD;
		*outfile_fd = ERROR_FD;
	}
}

void	get_redirect_fd(t_list *redirect, char **my_env, int *infile_fd, int *outfile_fd)
{
	int		heredoc_fd;
	char	*file_name;
	t_list	*current;
	t_list	*tmp;

	*infile_fd = NONE_FD;
	*outfile_fd = NONE_FD;
	heredoc_fd = NONE_FD;

	if (redirect == NULL)
		return ;

	file_name = NULL;
	current = redirect;
	while (current != NULL)
	{
		if (heredoc_fd != NONE_FD)
		{
			close(heredoc_fd);
		}
		file_name = current->content;
		if (file_name[0] == '<' && file_name[1] == '<')
			heredoc_fd = heredoc_open(file_name, my_env);
		current = current->next;
	}

	file_name = NULL;
	current = redirect;
	while (current != NULL)
	{
		file_name = current->content;
		if (file_name[0] != '<' || file_name[1] != '<')
		{
			if (ms_strncmp(file_name, ">>", 2) == 0)
				tmp = expand_cmd_info_element(ms_lstnew(ms_strdup(file_name + 3)), my_env);
			else
				tmp = expand_cmd_info_element(ms_lstnew(ms_strdup(file_name + 2)), my_env);
			if (ms_lstsize(tmp) != 1 || ms_strcmp(tmp->content, "") == 0)
			{
				put_error_exit(ms_strchr(file_name, '$'), get_g_status(), "ambiguous redirect", FALSE);
				*infile_fd = ERROR_FD;
				*outfile_fd = ERROR_FD;
				ms_lstclear(&tmp, free);
				return ;
			}
			else
			{
				if (ms_strncmp(file_name, ">>", 2) == 0)
					redirect_file_open(ms_strappend(ms_strdup(">> "), ms_strdup(tmp->content)),
										infile_fd, outfile_fd, heredoc_fd);
				else if (ms_strncmp(file_name, "<", 1) == 0)
					redirect_file_open(ms_strappend(ms_strdup("< "), ms_strdup(tmp->content)),
										infile_fd, outfile_fd, heredoc_fd);
				else
					redirect_file_open(ms_strappend(ms_strdup("> "), ms_strdup(tmp->content)),
										infile_fd, outfile_fd, heredoc_fd);
			}
			ms_lstclear(&tmp, free);
		}
		else
		{
			redirect_file_open(file_name, infile_fd, outfile_fd, heredoc_fd);
			if (*infile_fd == ERROR_FD || *outfile_fd == ERROR_FD)
				break ;
		}
		current = current->next;
	}
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
