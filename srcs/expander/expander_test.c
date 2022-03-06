/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:31:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/15 16:26:13 by tsekiguc         ###   ########.fr       */
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
	//print_cmds(cmds);
	expander(cmds);
	print_cmds(cmds);
	printf("***********test************\n\n");
}

int main(void)
{
	//test("");
	//test("aaa");
	//test("aaa   ");
	//test("aaa bbb ccc      ");
	//test("    aaa bbb ccc    ");
	//test("echo taiyou");
	//test("cat <infile -e | grep test | wc -l > outfile");
	//test("cat <infile <<infile2 -e | grep test | wc -l > outfile -e >> outfile2");
	//test("> outfile");
	//test("cat $HOME < $HOME | grep test | wc -l >> outfile > outfile");
	//test("cat \"-e $PWD\"");
	//test("cat \'-e $OLDPWD\'");
	//test("cat \'-e $HOME\"taiyou\"\'");
	//test("cat \"-e $SHLVL\'taiyou\'\"");
	//test("cat \'taiyou\'$HOME\'sekiguchi\'");
	test("cat $PATH");
	test("echo \"'$PATH'\"");
	test("echo \"'\\''$PATH'\"");
	test("echo \"\\'$PATH'\"");
	test("echo \"$USER '$TEST1'\"");
	test("echo '$'");
	test("echo '\"$PATH\"'");
	test("echo $TEST1");
	test("echo $TEST");
	return (0);
}
