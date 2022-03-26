#include "minishell.h"

/*void end(void)__attribute__((destructor));

void end(void)
{
	system("leaks expander_test");
}*/

void	print_list(t_list *list, char *kind)
{
	t_list	*current;

	printf("%-10s: ", kind);
	current = list;
	while (current != NULL)
	{
		printf("[%s] ", (char *)current->content);
		current = current->next;
	}
	printf("\n");
}

void	print_cmd(t_cmd_info *cmd)
{
	printf("**************\n");
	print_list(cmd->cmd, "cmd");
	print_list(cmd->infile, "infile");
	print_list(cmd->outfile, "outfile");
	printf("**************\n\n");
}

void	print_cmds(t_list *cmds)
{
	t_list	*current;

	current = cmds;
	while (current != NULL)
	{
		print_cmd(current->content);
		current = current->next;
	}
}

void	test(char *command, t_dir *d_info)
{
	t_list		*token_list;
	t_list		*cmd_info_list;
	t_list		*current;
	t_cmd_info	*cmd_info;

	printf("***********test************\n");
	printf("[command] : %s\n", command);
	token_list = NULL;
	lexer(&token_list, command);
	cmd_info_list = NULL;
	parser(&cmd_info_list, token_list);
	expander(cmd_info_list, d_info->my_env);
	print_cmds(cmd_info_list);
	ms_lstclear(&token_list, ms_free);
	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		ms_lstclear(&(cmd_info->cmd), ms_free);
		ms_lstclear(&(cmd_info->redirect), ms_free);
		current = current->next;
	}
	ms_lstclear(&(cmd_info_list), ms_free);
	printf("***********test************\n\n");
}

int	main(void)
{
	t_dir	info;

	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);
	test("\"/bin/ls srcs\"", &info);
	test("export TEST=\"-e hello\"", &info);
	test("echo \" $\"", &info);
	test("echo \"'\"", &info);
	return (0);
}

//test("echo \"\" \"\" \"\" ", &info);
//test("aaa bbb ccc      ", &info);
/*test("aaa");
test("aaa   ");
test("aaa bbb ccc      ");
test("    aaa bbb ccc    ");
test("echo taiyou");
test("cat <infile -e | grep test | wc -l > outfile");
test("cat <infile <<infile2 -e | grep test | wc -l > outfile -e >> outfile2");
test("> outfile");
test("cat $HOME < $HOME | grep test | wc -l >> outfile > outfile");
test("cat \"-e $PWD\"");
test("cat \'-e $OLDPWD\'");
test("cat \'-e $HOME\"taiyou\"\'");
test("cat \"-e $SHLVL\'taiyou\'\"");
test("cat \'taiyou\'$HOME\'sekiguchi\'");
test("cat $PATH");
test("echo \"'$PATH'\"");
test("echo \"'\\''$PATH'\"");
test("echo \"\\'$PATH'\"");
test("echo \"$USER '$TEST1'\"");
test("echo '$'");
test("echo '\"$PATH\"'");
test("echo $TEST1");
test("echo $TEST");
test("echo $1TEST");
test("echo $13TEST");
test("echo $13TEST$$");
test("echo $13TEST$$$");
test("echo $+TEST");
test("echo $!TEST");
test("echo $ TEST");
test("echo \'$1TEST\'");
test("cat <<<end");
test("cat <<<Makefile");
test("cat Makefile'");*/
