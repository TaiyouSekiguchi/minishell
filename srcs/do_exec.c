/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:10:22 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/04 18:19:06 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_kind
distinguish_redirect_kind(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

void	infile_redirect_part(t_list *infile)
{
	t_list	*current;
	t_kind	kind;

	current = infile;
	if (current != NULL)
	{
		kind = distinguish_redirect_kind(current->content);
		do_redirect(current->content, kind);
	}
}

char
**make_argv_for_execve(t_list *cmd, size_t cmd_token_count)
{
	char	**argv;
	t_list	*current;
	size_t	i;

	argv = (char **)ms_xmalloc(sizeof(char *) * (cmd_token_count + 1));
	current = cmd;
	i = 0;
	while (current != NULL)
	{
		argv[i] = current->content;
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char
*add_path(char *cmd_name)
{
	char	*env_path;
	char	**split_path;
	char	*full_path;
	size_t	i;
	struct stat	buf;

	env_path = getenv("PATH");
	if (env_path == NULL)
		ms_error("PATH is nothing");

	split_path = ms_split(env_path, ':');
	full_path = NULL;
	i = 0;
	while (split_path[i] != NULL)
	{
		full_path = ms_strjoin(split_path[i], "/");
		full_path = ms_strappend(full_path, cmd_name);
		if (stat(full_path, &buf) == 0)
		{
			free(cmd_name);
			ms_split_free(split_path);
			return (full_path);
		}
		else
			i++;
	}
	ms_split_free(split_path);
	if (stat(cmd_name, &buf) == 0)
		return (cmd_name);
	return (NULL);
}

void
do_exec(t_cmd *cmd_group)
{
	extern char		**environ;
	char			**argv;
	size_t			cmd_token_count;

	//redirect part
	infile_redirect_part(cmd_group->infile);

	//parse from list to array for execve
	cmd_token_count = ms_lstsize(cmd_group->cmd);
	argv = make_argv_for_execve(cmd_group->cmd, cmd_token_count);

	//command search

	//exec part
	if (is_builtin(argv[0]))
	{
		do_builtin(argv[0], cmd_token_count, argv);
	}
	else
	{
		argv[0] = add_path(argv[0]);
		if (argv[0] == NULL)
			ms_error("minishell command not found");

		if (execve(argv[0], argv, environ) < 0)
		{
			ms_putendl_fd(argv[0], STDERR_FILENO);
			perror("execve");
			ms_error("execve failed");
		}
	}
}
