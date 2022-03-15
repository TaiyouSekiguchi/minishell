#include "minishell.h"

/*void end(void)__attribute__((destructor));

void end(void)
{
	system("leaks executer_test");
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

void	print_cmd(t_cmd_info *cmd_info)
{
	printf("\n");
	print_list(cmd_info->cmd, "cmd");
	print_list(cmd_info->infile, "infile");
	print_list(cmd_info->outfile, "outfile");
	printf("\n\n");
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

void	test(t_dir *info, char *command)
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
	expander(cmd_info_list);
	print_cmds(cmd_info_list);
	executer(cmd_info_list, info);
	printf("***********test************\n\n");

	//free part
	ms_lstclear(&token_list, free);
	current = cmd_info_list;
	while (current != NULL)
	{
		cmd_info = current->content;
		ms_lstclear(&(cmd_info->infile), free);
		ms_lstclear(&(cmd_info->cmd), free);
		ms_lstclear(&(cmd_info->outfile), free);
		current = current->next;
	}
	ms_lstclear(&(cmd_info_list), free);
}

int main(void)
{
	t_dir	info;

	init_my_env(&info);
	init_dir_info(&info);
	init_shlvl(&info.my_env);

	test(&info, "cat");
	test(&info, "cat < Makefile");
	test(&info, "cat << END");
	test(&info, "cat < Makefile | wc -l");
	test(&info, "cat < Makefile | wc -l > outfile1");
	test(&info, "cat < Makefile | wc -l >> outfile1");
	test(&info, "cat < Makefile | grep a | wc -l >> outfile2");
	test(&info, "cat < Makefile < .gitignore | grep a | wc -l >> outfile2");
	//test(&info, "cat < Makefile < .gitignore | grep a | wc -l >> outfile2");
	//test(&info, "cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	//test(&info, "cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	//test(&info, "cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	//test(&info, "cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	//test(&info, "cat < Makefile << END < .gitignore | grep a | wc -l >> outfile3");
	//test(&info, "cat < Makefile << END | grep a < .gitignore | wc -l >> outfile4");
	//test(&info, "cat < Makefile << END | grep a < .gitignore | wc -l >> outfile4");
	//test(&info, "cat < Makefile > outfile5 | cat -e");
	
	free(info.pwd);
	free(info.old_pwd);
	//system("leaks executer_test");
	return (0);
}
