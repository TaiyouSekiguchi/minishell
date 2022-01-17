/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:31:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/14 11:05:54 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	test(char *str)
{
	t_list	*tokens;
	t_list	*current;
	size_t	i;

	printf("***********test************\n");
	printf("test str is %s!!\n", str);
	tokens = NULL;
	lexer(&tokens, str);
	
	i = 0;
	current = tokens;
	while (current != NULL)
	{
		printf("tokens[%zu] is %s\n", i, (char *)current->content);
		i++;
		current = current->next;
	}
	ft_lstclear(&tokens, free);
	printf("***********test************\n");
}

int main(void)
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
//	system("leaks minishell");
	return (0);
}
