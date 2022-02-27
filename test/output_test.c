#include "minishell.h"

void	test(char *str, t_dir *d_info)
{
	t_list	*tokens;
	t_list	*cmds;

	tokens = NULL;
	lexer(&tokens, str);
	cmds = NULL;
	parser(&cmds, tokens);
	expander(cmds);
	executer(cmds, d_info);
}

int	main(int argc, char **argv)
{
	char	*command;
	t_dir	info;
	int		i;

	if (argc < 2)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		if (i == 1)
			command = ms_strdup(argv[1]);
		else
			command = ms_strjoin(command, argv[i]);
		command = ms_strjoin(command, " ");
		i++;
	}
	init_dir_info(&info);
	test(command, &info);
	return (g_status);
}
