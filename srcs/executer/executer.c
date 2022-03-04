
#include "minishell.h"

extern int g_status;

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

pid_t	do_cmd(t_cmd_info *cmd_info, t_boolean is_last, t_dir *d_info)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	//タイミング制御のため前に切り出した
	infile_fd = get_redirect_fd(cmd_info->infile);
	outfile_fd = get_redirect_fd(cmd_info->outfile);

	if (is_last == TRUE)
	{
		pid = fork();
		if (pid == CHILD)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);

			do_redirect(infile_fd, outfile_fd);
			do_exec(cmd_info, d_info);
			exit(g_status);
		}
		else
		{
			close(infile_fd);
			close(outfile_fd);
			close(STDIN);
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

			do_redirect(infile_fd, outfile_fd);
			do_exec(cmd_info, d_info);
			exit(g_status);
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

void	exec_process(t_list *cmd_info_list, t_dir *d_info)
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

	exit(return_status(last_status));
}

void	executer(t_list *cmd_info_list, t_dir *d_info)
{
	t_cmd_info	*first_cmd_info;
	pid_t		pid;
	int			status;

	first_cmd_info = cmd_info_list->content;
	if (is_builtin(first_cmd_info->cmd->content)
		&& ms_lstsize(cmd_info_list) == 1)
	{
		do_exec(first_cmd_info, d_info);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == CHILD)
		{
			exec_process(cmd_info_list, d_info);
		}
		else
		{
			wait(&status);
			signal(SIGINT, sigint_handler);
			g_status = WEXITSTATUS(status);
		}
	}
}
