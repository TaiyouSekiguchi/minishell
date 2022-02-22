
#include "minishell.h"

extern int g_status;

void	do_cmd(t_cmd *cmd_group, t_boolean is_last, t_dir *d_info)
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
		do_exec(cmd_group, d_info);
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
			do_exec(cmd_group, d_info);
		}
		else
		{
			close(pipe_fd[WRITE]);
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
	}
}

void	exec_process(t_list *cmds, t_dir *d_info)
{
	t_list *last_elem;

	last_elem = ms_lstlast(cmds);
	while (cmds != NULL)
	{
		if (cmds == last_elem)
			do_cmd(cmds->content, TRUE, d_info);
		else
			do_cmd(cmds->content, FALSE, d_info);
		cmds = cmds->next;
		wait(&g_status);
	}
}

void	executer(t_list *cmds, t_dir *d_info)
{
	t_cmd	*first_cmd_group;
	char	*first_cmd_name;
	int		cmd_group_count;
	pid_t	ret;
	int		status;
	
	first_cmd_group = cmds->content;
	first_cmd_name = first_cmd_group->cmd->content;
	cmd_group_count = ms_lstsize(cmds);
	if (is_builtin(first_cmd_name) && cmd_group_count == 1)
	{
		do_exec(first_cmd_group, d_info);
	}
	else
	{
		ret = fork();
		if (ret == 0)
		{
			exec_process(cmds, d_info);
		}
		else
		{
			wait(&status);
			g_status = WEXITSTATUS(status);
		}
	}
}
