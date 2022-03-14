#include "minishell.h"

pid_t	do_cmd(t_cmd_info *cmd_info, t_boolean is_last, t_dir *d_info)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	get_redirect_fd(cmd_info->redirect, d_info->my_env, &infile_fd, &outfile_fd);
	/*infile_fd = get_redirect_fd(cmd_info->infile, d_info->my_env);
	if (infile_fd != ERROR_FD)
		outfile_fd = get_redirect_fd(cmd_info->outfile, d_info->my_env);
	else
		outfile_fd = ERROR_FD;*/

	if (is_last == TRUE)
	{
		pid = fork();
		if (pid == CHILD)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);

			if (infile_fd != ERROR_FD && outfile_fd != ERROR_FD)
			{
				do_redirect(infile_fd, outfile_fd);

				if (cmd_info->cmd != NULL)
					do_exec(cmd_info, d_info);

			}
			close(infile_fd);
			close(outfile_fd);
			exit(get_g_status());
		}
		else
		{
			close(infile_fd);
			close(outfile_fd);
			close(STDIN);
			open("/dev/tty", O_RDONLY);
		}
	}
	else
	{
		if (pipe(pipe_fd) == -1)
			perror("minishell");
		pid = fork();
		if (pid == CHILD)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);

			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT);

			if (infile_fd != ERROR_FD && outfile_fd != ERROR_FD)
			{
				do_redirect(infile_fd, outfile_fd);

				if (cmd_info->cmd != NULL)
					do_exec(cmd_info, d_info);

			}

			close(infile_fd);
			close(outfile_fd);
			exit(get_g_status());
		}
		else
		{
			close(infile_fd);
			close(outfile_fd);
			close(pipe_fd[WRITE]);
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
	}
	return (pid);
}

static int	return_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ms_putchar_fd('\n', STDOUT);
		else if (WTERMSIG(status) == SIGQUIT)
			ms_putendl_fd("Quit: 3", STDOUT);
		else if (WTERMSIG(status) == SIGTERM)
			ms_putendl_fd("Terminated: 15", STDOUT);
		return (128 + WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	else
		return (1);
}

static int	exec_process(t_list *cmd_info_list, t_dir *d_info)
{
	pid_t	ret_pid;
	pid_t	last_pid;
	int		status;
	int		last_status;

	//last_elem = ms_lstlast(cmd_info_list);
	while (cmd_info_list->next != NULL)
	{
		last_pid = do_cmd(cmd_info_list->content, FALSE, d_info);
		cmd_info_list = cmd_info_list->next;
	}
	last_pid = do_cmd(cmd_info_list->content, TRUE, d_info);

	ret_pid = 0;
	while (ret_pid >= 0)
	{
		ret_pid = waitpid(-1, &status, 0);
		if (ret_pid == last_pid)
			last_status = status;
	}

	return (return_status(last_status));
}

static void	tty_reset(void)
{
	if (!isatty(0) && !isatty(1))
	{
		close(0);
		close(1);
		open("/dev/tty", O_RDONLY);
		open("/dev/tty", O_WRONLY);
	}
	else if (!isatty(0))
	{
		close(0);
		open("/dev/tty", O_RDONLY);
	}
	else
	{
		close(1);
		open("/dev/tty", O_WRONLY);
	}
}

void	executer(t_list *cmd_info_list, t_dir *d_info)
{
	t_cmd_info	*first_cmd_info;
	int			infile_fd;
	int			outfile_fd;
	//pid_t		pid;
	//int			status;

	first_cmd_info = cmd_info_list->content;
	if (first_cmd_info->cmd != NULL
		&& is_builtin(first_cmd_info->cmd->content)
		&& ms_lstsize(cmd_info_list) == 1)
	{
		get_redirect_fd(first_cmd_info->redirect, d_info->my_env, &infile_fd, &outfile_fd);
		/*infile_fd = get_redirect_fd(first_cmd_info->infile, d_info->my_env);
		if (infile_fd != ERROR_FD)
			outfile_fd = get_redirect_fd(first_cmd_info->outfile, d_info->my_env);
		else
			outfile_fd = ERROR_FD;*/


		do_redirect(infile_fd, outfile_fd);

		do_exec(first_cmd_info, d_info);
		tty_reset();
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		set_g_status(exec_process(cmd_info_list, d_info));
		signal(SIGINT, sigint_handler);
		/*signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == CHILD)
		{
			exec_process(cmd_info_list, d_info);
		}
		else
		{
			wait(&status);
			signal(SIGINT, sigint_handler);
			set_g_status(WEXITSTATUS(status));
		}*/
	}
}
