#include "minishell.h"

void end(void)__attribute__((destructor));

void end(void)
{
	system("leaks parser_test");
}

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
	printf("\n");
	print_list(cmd->cmd, "cmd");
	print_list(cmd->infile, "infile");
	print_list(cmd->outfile, "outfile");
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

void	test(char *command)
{
	t_list	*tokens;
	t_list	*cmds;

	t_cmd_info	*cmd_info;
	printf("***********test start************\n");
	printf("[command] : %s\n", command);
	tokens = NULL;
	lexer(&tokens, command);
	cmds = NULL;
	parser(&cmds, tokens);
	print_cmds(cmds);

	//tokens, cmds, free
	ms_lstclear(&tokens, free);
	t_list	*current = cmds;
	while (current != NULL)
	{
		cmd_info = current->content;
		ms_lstclear(&(cmd_info->infile), free);
		ms_lstclear(&(cmd_info->cmd), free);
		ms_lstclear(&(cmd_info->outfile), free);
		current = current->next;
	}
	ms_lstclear(&(cmds), free);
	printf("***********test finish***********\n\n\n");
}

int main(void)
{
	test("");
	test("aaa");
	test("aaa   ");
	test("aaa bbb ccc      ");
	test("    aaa bbb ccc    ");
	test("echo taiyou");
	test("cat <infile -e | grep test | wc -l > outfile");
	test("cat <infile <<infile2 -e | grep test | wc -l > outfile -e >> outfile2");
	test("> outfile");
	test("cat < $TEST | grep test | wc -l >> outfile > outfile");
	test("cat Makefile | wc -l");
	test("cat <");
	test("> outfile |");
	return (0);
}
