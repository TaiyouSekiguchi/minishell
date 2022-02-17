/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:31:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/17 19:57:15 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

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

void	print_cmd(t_cmd *cmd)
{
	printf("\n");
	print_list(cmd->cmd, "cmd");
	print_list(cmd->infile, "infile");
	print_list(cmd->outfile, "outfile");
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

void	test(char *str)
{
	t_list	*tokens;
	t_list	*cmds;

	printf("***********test************\n");
	printf("[command] : %s\n", str);
	tokens = NULL;
	lexer(&tokens, str);
	cmds = NULL;
	parser(&cmds, tokens);
	expander(cmds);
	print_cmds(cmds);
	printf("***********test************\n\n");
	executer(cmds);
}

int main(void)
{
	//test("cat");
	//test("cat < Makefile");
	//test("cat << END");
	//test("cat < Makefile | wc -l");
	//test("cat < Makefile | wc -l > outfile1");
	//test("cat < Makefile | wc -l >> outfile1");
	test("cat < Makefile | grep a | wc -l >> outfile2");
	test("cat < Makefile < .gitignore | grep a | wc -l >> outfile2");
	test("cat < Makefile < .gitignore | grep a | wc -l >> outfile2");
	test("cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	test("cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	test("cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	test("cat < Makefile < .gitignore << END | grep a | wc -l >> outfile3");
	test("cat < Makefile << END < .gitignore | grep a | wc -l >> outfile3");
	test("cat < Makefile << END | grep a < .gitignore | wc -l >> outfile4");
	test("cat < Makefile << END | grep a < .gitignore | wc -l >> outfile4");
	test("cat < Makefile > outfile5 | cat -e");
	return (0);
}
