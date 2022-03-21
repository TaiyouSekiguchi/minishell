#include "minishell.h"

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

void	executer(t_list *cmd_info_list, t_dir *d_info)
{
	t_cmd_info	*first_cmd_info;
	t_fd		redirect_fd;

	first_cmd_info = cmd_info_list->content;
	if (first_cmd_info->cmd != NULL
		&& is_builtin(first_cmd_info->cmd->content)
		&& ms_lstsize(cmd_info_list) == 1)
	{
		get_redirect_fd(first_cmd_info->redirect, d_info->my_env, &redirect_fd);
		do_redirect(&redirect_fd);
		do_exec(first_cmd_info, d_info);
		tty_reset();
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		set_g_status(exec_process(cmd_info_list, d_info));
		signal(SIGINT, sigint_handler);
	}
}
