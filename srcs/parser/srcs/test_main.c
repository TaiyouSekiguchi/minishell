/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:31:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/14 11:22:27 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	print_array(char **str, char *kind)
{
	int		i;

	printf("%s : ", kind);
	i = 0;
	while (str[i] != NULL)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

void	print_cmds(t_cmd *cmds, int cmds_cnt)
{
	int		i;

	i = 0;
	while (i < cmds_cnt)
	{
		print_array(cmds[i].cmd, "cmd");
		print_array(cmds[i].infile, "infile");
		print_array(cmds[i].outfile, "outfile");
		i++;
	}
}

void	test(char *str)
{
	t_list	*tokens;
	t_cmd	*cmds;
	int		cmds_cnt;

	printf("***********test************\n");
	printf("test str is %s!!\n", str);
	tokens = NULL;
	lexer(&tokens, str);
	parser(&cmds, &cmds_cnt, tokens);
	print_cmds(cmds, cmds_cnt);
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
	test("cat <infile -e | grep test | wc -l > outfile");
	return (0);
}
