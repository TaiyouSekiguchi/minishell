
#include "minishell.h"

extern int g_status;

void	do_cmd(t_cmd *cmd_group, t_boolean is_last)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	if (is_last == TRUE)
	{
		infile_fd = get_redirect_fd(cmd_group->infile);
		outfile_fd = get_redirect_fd(cmd_group->outfile);
		do_redirect(infile_fd, outfile_fd);
		do_exec(cmd_group);
	}
	else
	{
		if (pipe(pipe_fd) == -1)
			perror("minishell");
		pid = fork();
		if (pid == 0)
		{
			infile_fd = get_redirect_fd(cmd_group->infile);
			outfile_fd = get_redirect_fd(cmd_group->outfile);
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT);
			do_redirect(infile_fd, outfile_fd);
			do_exec(cmd_group);
		}
		else
		{
			close(pipe_fd[WRITE]);
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
	}
}

void	exec_process(t_list *cmds)
{
	t_list *last_elem;

	last_elem = ms_lstlast(cmds);
	while (cmds != NULL)
	{
		if (cmds == last_elem)
			do_cmd(cmds->content, TRUE);
		else
			do_cmd(cmds->content, FALSE);
		cmds = cmds->next;
		wait(&g_status);
	}
}

void	executer(t_list *cmds)
{
	pid_t	ret;
	int		status;

	ret = fork();
	if (ret == 0)
	{
		exec_process(cmds);
	}
	else
	{
		wait(&status);
		g_status = WEXITSTATUS(status);
	}
}
