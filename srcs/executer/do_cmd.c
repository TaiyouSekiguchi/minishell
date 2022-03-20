#include "minishell.h"

static void	close_redirect_fd(t_fd *redirect_fd, t_boolean last)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = redirect_fd->infile;
	outfile_fd = redirect_fd->outfile;
	close(infile_fd);
	close(outfile_fd);
	if (last == TRUE)
		tty_reset();
}

static void	pipe_set(int src, int dst, int not_use)
{
	close(not_use);
	close(dst);
	dup2(src, dst);
	close(src);
}

static pid_t	last_cmd(t_cmd_info *cmd_info, t_dir *info, t_fd *redirect_fd)
{
	pid_t		pid;

	pid = fork();
	if (pid == CHILD)
	{
		default_signal();
		if (redirect_fd->infile != ERROR_FD && redirect_fd->outfile != ERROR_FD)
		{
			do_redirect(redirect_fd);
			if (cmd_info->cmd != NULL)
				do_exec(cmd_info, info);
		}
		exit(get_g_status());
	}
	else
		close_redirect_fd(redirect_fd, TRUE);
	return (pid);
}

static pid_t
	not_last_cmd(t_cmd_info *cmd_info, t_dir *d_info, t_fd *redirect_fd)
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
		if (redirect_fd->infile != ERROR_FD && redirect_fd->outfile != ERROR_FD)
		{
			do_redirect(redirect_fd);
			if (cmd_info->cmd != NULL)
				do_exec(cmd_info, d_info);
		}
		exit(get_g_status());
	}
	else
	{
		pipe_set(pipe_fd[READ], STDIN, pipe_fd[WRITE]);
		close_redirect_fd(redirect_fd, FALSE);
	}
	return (pid);
}

pid_t	do_cmd(t_cmd_info *cmd_info, t_boolean is_last, t_dir *d_info)
{
	int		pid;
	t_fd	redirect_fd;

	get_redirect_fd(cmd_info->redirect, d_info->my_env, &redirect_fd);
	if (is_last == TRUE)
		pid = last_cmd(cmd_info, d_info, &redirect_fd);
	else
		pid = not_last_cmd(cmd_info, d_info, &redirect_fd);
	return (pid);
}
