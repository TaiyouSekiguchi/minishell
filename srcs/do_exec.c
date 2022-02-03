/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:19:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/03 14:51:56 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_kind	distinguish_redirect_kind(char	*str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else
		return (INFILE);
}

void	infile_redirect_part(t_list *infile)
{
	t_list	*current;
	t_kind	redirect;

	current = infile;
	if (current != NULL)
	{
		redirect = distinguish_redirect_kind(current->content);
		do_redirect(current->content, redirect);
	}
}


void	do_exec(t_cmd *cmd)
{
	extern char		**environ;
	char			**argv;
	t_list			*current;
	size_t			len;
	size_t			i;
	t_builtin		result;


	//redirect part
	infile_redirect_part(cmd->infile);
	/*current = cmd->infile;
	if (current != NULL)
	{
		tmp = ms_strdup(current->content);
		kind = infile_check(tmp);
		do_redirect(tmp, kind);
	}*/

	//parse from list to array for execve
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



	//exec part
	result = builtin_check(argv[0]);
	if (result != NOT_BUILTIN)
	{
		do_builtin(result, len, argv);
	}
	else if (execve(argv[0], argv, environ) < 0)
	{
		ms_putendl_fd(argv[0], STDERR_FILENO);
		perror("execve");
		ms_error("execve failed");
	}
}
