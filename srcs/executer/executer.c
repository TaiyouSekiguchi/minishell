
#include "minishell.h"

extern int g_status;

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit_handler(int signum)
{
	ms_putendl_fd("Quit: 3", STDERR);
	if (signum == SIGQUIT)
	{
		ms_putendl_fd("Quit: 3", STDERR);
		exit(131);
	}
}

pid_t	do_cmd(t_cmd *cmd_group, t_boolean is_last, t_dir *d_info, int stdin_save)
{
	int	pipe_fd[2];
	int	pid;
	int	infile_fd;
	int	outfile_fd;

	//タイミング制御のため前に切り出した
	infile_fd = get_redirect_fd(cmd_group->infile, stdin_save);
	outfile_fd = get_redirect_fd(cmd_group->outfile, stdin_save);

	if (is_last == TRUE)
	{
		pid = fork();
		if (pid == 0)
		{

			signal(SIGQUIT, sigquit_handler);
			signal(SIGINT, SIG_DFL);

			do_redirect(infile_fd, outfile_fd);
			do_exec(cmd_group, d_info);

			//for builtin
			exit(g_status);
		}
		else
		{
			//親プロセスでは不要のためclose
			close(infile_fd);
			close(outfile_fd);

			//これは前のコマンドのパイプとつながっている。
			//親プロセスでは不要
			close(STDIN);
		}
	}
	else
	{
		if (pipe(pipe_fd) == -1)
			perror("minishell");
		pid = fork();
		if (pid == 0)
		{

			signal(SIGQUIT, sigquit_handler);
			signal(SIGINT, SIG_DFL);
			//signal(SIGQUIT, SIG_DFL);

			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT);
			do_redirect(infile_fd, outfile_fd);
			do_exec(cmd_group, d_info);

			//for builtin
			exit(g_status);
		}
		else
		{
			//親プロセスでは不要のためclose
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
		if (WTERMSIG(status) == SIGQUIT)
		{
			ms_putendl_fd("Quit: 3", STDOUT);
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			ms_putchar_fd('\n', STDOUT);
		}
		return (128 + WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	else
		return (1);
}

void	exec_process(t_list *cmds, t_dir *d_info)
{
	t_list *last_elem;

	//追加部分
	pid_t	ret_pid;
	pid_t	last_pid;
	int		status;
	int		last_status;

	//パイプ後ヒアドキュメントのためstdinを複製
	int		stdin_save;
	stdin_save = dup(STDIN);

	last_elem = ms_lstlast(cmds);
	while (cmds != NULL)
	{
		if (cmds == last_elem)
			last_pid = do_cmd(cmds->content, TRUE, d_info, stdin_save);
		else
			last_pid = do_cmd(cmds->content, FALSE, d_info, stdin_save);
		cmds = cmds->next;
		//したでまとめてwaitするので削除
		//wait(&g_status);
	}

	//まとめてwait追加
	ret_pid = 0;
	while (ret_pid >= 0)
	{
		ret_pid = waitpid(-1, &status, 0);
		if (ret_pid == last_pid)
			last_status = status;
	}

	exit(return_status(last_status));
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
		signal(SIGINT, SIG_IGN);
		ret = fork();
		if (ret == 0)
		{
			//signal(SIGQUIT, SIG_DFL);
			exec_process(cmds, d_info);
		}
		else
		{
			wait(&status);
			signal(SIGINT, sig_handler);
			g_status = WEXITSTATUS(status);
		}
	}
}
