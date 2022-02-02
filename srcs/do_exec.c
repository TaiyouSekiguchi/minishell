/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/02 16:04:14 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_kind	infile_check(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

void	do_exec(t_cmd *cmd)
{
	extern char		**environ;
	char			**argv;
	t_list			*current;
	size_t			len;
	size_t			i;
	int				ret;
	char			*tmp;
	t_kind			kind;

	current = cmd->infile;
	if (current != NULL)
	{
		tmp = ms_strdup(current->content);
		kind = infile_check(tmp);
		do_redirect(tmp, kind);
	}

	len = ms_lstsize(cmd->cmd);
	argv = (char **)ms_xmalloc(sizeof(char *) * (len + 1));

	i = 0;
	current = cmd->cmd;
	while (current != NULL)
	{
		argv[i] = current->content;
		i++;
		current = current->next;
	}
	argv[i] = NULL;

	ret = is_builtin(argv[0]);
	if (ret != NO_BUILTIN)
	{
		do_builtin(ret, len, argv);
	}
	else if (execve(argv[0], argv, environ) < 0)
	{
		ms_putendl_fd(argv[0], STDERR_FILENO);
		perror("execve");
		ms_error("execve failed");
	}
}
