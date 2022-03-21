#include "minishell.h"

void	test(char *str)
{
	t_list	*tokens;
	t_list	*current;
	size_t	i;

	printf("\n***********test start************\n");
	printf("[command] : %s\n", str);
	tokens = NULL;
	lexer(&tokens, str);
	i = 0;
	current = tokens;
	while (current != NULL)
	{
		printf("tokens[%zu] : %s\n", i, (char *)current->content);
		i++;
		current = current->next;
	}
	ms_lstclear(&tokens, free);
	printf("***********test finish***********\n");
}

int	main(void)
{
	test("");
	test("aaa");
	test("aaa   ");
	test("aaa bbb ccc      ");
	test("    aaa bbb ccc    ");
	test("echo taiyou");
	test("echo \"taiyou\"sekiguchi");
	test("echo \"taiyou\" sekiguchi");
	test("echo \"ta\"i\"you\"sekiguchi");
	test("echo taiyou>file");
	test("echo \"taiyou>file\"");
	test("echo \"taiy\'ou>file\"");
	test("aaa ; bbb|<");
	test("echo >> taiyou");
	test("echo > > taiyou");
	test("echo 'sekiguchi taiyou'");
	test("echo \"sekiguchi taiyou\"");
	test("echo \"hello w\"'orld'; cat<file|wc");
	test("echo \"hello w\"'orld'; cat<file|wc|<");
	test("cat < Makefile | grep OBJS | wc -l > outfile");
	test("cat <infile -e | grep test | wc -l > outfile");
	test("cat <infile \"-e $TEST\"");
	test("echo \"\" \"\" \"\" ");
	test(">out1 > out2");
	return (0);
}
