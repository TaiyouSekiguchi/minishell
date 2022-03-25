#include "minishell.h"

void	test(char *command, t_dir *d_info)
{
	t_list	*token_list;
	t_list	*cmd_info_list;

	if (command[0] == '\0')
		return ;
	token_list = NULL;
	lexer(&token_list, command);
	if (token_list == NULL)
		return ;
	cmd_info_list = NULL;
	parser(&cmd_info_list, token_list);
	if (cmd_info_list == NULL)
	{
		ms_lstclear(&token_list, ms_free);
		return ;
	}
	expander(cmd_info_list, d_info->my_env);
	executer(cmd_info_list, d_info);
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
	init(&info);
	test(command, &info);
	main_free(&info);
	return (get_g_status());
}
