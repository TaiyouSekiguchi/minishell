#include "minishell.h"

static void	close_redirect_fd(int infile_fd, int outfile_fd, t_boolean last)
{
	close(infile_fd);
	close(outfile_fd);
	if (last == TRUE)
		tty_reset();
}

static void pipe_set(int src, int dst, int not_use)
{
	close(not_use);
	close(dst);
	dup2(src, dst);
	close(src);
}

static pid_t	last_cmd(t_cmd_info *cmd_info, t_dir *d_info, int infile_fd, int outfile_fd)
{
	pid_t		pid;

	pid = fork();
	if (pid == CHILD)
	{
		default_signal();
		if (infile_fd != ERROR_FD && outfile_fd != ERROR_FD)
		{
			do_redirect(infile_fd, outfile_fd);
			if (cmd_info->cmd != NULL)
				do_exec(cmd_info, d_info);
		}
		exit(get_g_status());
	}
	else
		close_redirect_fd(infile_fd, outfile_fd, TRUE);
	return (pid);
}

static pid_t	not_last_cmd(t_cmd_info *cmd_info, t_dir *d_info, int infile_fd, int outfile_fd)
{
	int			pipe_fd[2];
	pid_t		pid;

	if (pipe(pipe_fd) == -1)
		perror("minishell");
	pid = fork();
	if (pid == CHILD)
	{
		default_signal();
		pipe_set(pipe_fd[WRITE], STDOUT, pipe_fd[READ]);
		if (infile_fd != ERROR_FD && outfile_fd != ERROR_FD)
		{
			do_redirect(infile_fd, outfile_fd);
			if (cmd_info->cmd != NULL)
				do_exec(cmd_info, d_info);
		}
		exit(get_g_status());
	}
	else
	{
		pipe_set(pipe_fd[READ], STDIN, pipe_fd[WRITE]);
		close_redirect_fd(infile_fd, outfile_fd, FALSE);
	}
	return (pid);
}

pid_t	do_cmd(t_cmd_info *cmd_info, t_boolean is_last, t_dir *d_info)
{
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	get_redirect_fd(cmd_info->redirect, d_info->my_env, &infile_fd, &outfile_fd);
	if (is_last == TRUE)
		pid = last_cmd(cmd_info, d_info, infile_fd, outfile_fd);
	else
		pid = not_last_cmd(cmd_info, d_info, infile_fd, outfile_fd);
	return (pid);
}
