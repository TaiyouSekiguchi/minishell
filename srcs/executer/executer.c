
#include "minishell.h"

extern int g_status;

void	do_cmd(t_cmd *cmd_group, t_boolean is_last)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		perror("minishell");
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (is_last != TRUE)
			dup2(pipe_fd[1], STDOUT_FILENO);
		do_exec(cmd_group);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	executer(t_list *cmds)
{
	size_t	cmd_len;
	size_t	i;

	cmd_len = ms_lstsize(cmds);
	i = cmd_len;
	while (cmd_len)
	{
		if (cmd_len == 1)
			do_cmd(cmds->content, TRUE);
		else
			do_cmd(cmds->content, FALSE);
		cmds = cmds->next;
		cmd_len--;
	}
	while (i)
	{
		wait(&g_status);
		i--;
	}
}
