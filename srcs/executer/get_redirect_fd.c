#include "minishell.h"

static void	redirect_file_open(char *file_name, t_fd *redirect_fd)
{
	if (file_name[0] == '<' && file_name[1] == ' ')
		redirect_fd->infile = infile_open(file_name);
	else if (file_name[0] == '<' && file_name[1] == '<')
		redirect_fd->infile = redirect_fd->heredoc;
	else if (file_name[0] == '>' && file_name[1] == ' ')
		redirect_fd->outfile = outfile_open(file_name);
	else if (file_name[0] == '>' && file_name[1] == '>')
		redirect_fd->outfile = append_open(file_name);
	else
	{
		redirect_fd->infile = ERROR_FD;
		redirect_fd->outfile = ERROR_FD;
	}
}

static int	get_heredoc_fd(t_list *redirect, char **my_env)
{
	int		heredoc_fd;
	char	*file_name;
	t_list	*current;

	heredoc_fd = NONE_FD;
	current = redirect;
	while (current != NULL)
	{
		if (heredoc_fd != NONE_FD)
		{
			close(heredoc_fd);
		}
		file_name = current->content;
		if (is_heredoc(file_name))
			heredoc_fd = heredoc_open(file_name, my_env);
		current = current->next;
	}
	return (heredoc_fd);
}

static t_list	*expand_file_name(char *file_name, char **my_env)
{
	char	*tmp;

	if (ms_strncmp(file_name, ">>", 2) == 0)
		tmp = ms_strdup(file_name + 3);
	else
		tmp = ms_strdup(file_name + 2);
	return (expand_cmd_info_element(ms_lstnew(tmp), my_env));
}

static void	expand_and_get_fd(char *file_name, char **my_env, t_fd *redirect_fd)
{
	t_list	*tmp_list;
	char	*tmp;
	char	*prefix;

	tmp_list = expand_file_name(file_name, my_env);
	if (ms_lstsize(tmp_list) != 1 || ms_strcmp(tmp_list->content, "") == 0)
	{
		put_error_exit(ms_strchr(file_name, '$'), "ambiguous redirect", FALSE);
		redirect_fd->infile = ERROR_FD;
		redirect_fd->outfile = ERROR_FD;
	}
	else
	{
		tmp = ms_strdup(tmp_list->content);
		if (ms_strncmp(file_name, ">>", 2) == 0)
			prefix = ">> ";
		else if (ms_strncmp(file_name, "<", 1) == 0)
			prefix = "< ";
		else
			prefix = "> ";
		tmp = ms_strappend(ms_strdup(prefix), tmp);
		redirect_file_open(tmp, redirect_fd);
		free(tmp);
	}
	ms_lstclear(&tmp_list, free);
}

void	get_redirect_fd(t_list *redirect, char **my_env, t_fd *redirect_fd)
{
	char	*file_name;
	t_list	*current;

	redirect_fd->infile = NONE_FD;
	redirect_fd->outfile = NONE_FD;
	redirect_fd->heredoc = NONE_FD;
	if (redirect == NULL)
		return ;
	redirect_fd->heredoc = get_heredoc_fd(redirect, my_env);
	current = redirect;
	while (current != NULL)
	{
		file_name = current->content;
		if (!is_heredoc(file_name))
			expand_and_get_fd(file_name, my_env, redirect_fd);
		else
			redirect_file_open(file_name, redirect_fd);
		if (redirect_fd->infile == ERROR_FD
			|| redirect_fd->outfile == ERROR_FD)
			break ;
		current = current->next;
	}
}
