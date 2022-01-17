/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:41:57 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/14 11:51:29 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	cmds_part(t_cmd **cmds, int *cmds_cnt, t_list *tokens)
{
	t_list	*current;

#ifdef DEBUG
	printf("***cmds_part***\n");
#endif
	*cmds_cnt = 1;
	current = tokens;
	while (current != NULL)
	{
		if (ft_strcmp(current->content, "|") == 0)
			*cmds_cnt += 1;
		current = current->next;
	}

#ifdef DEBUG
	printf("cmds_cnt is %d\n", *cmds_cnt);
#endif

	*cmds = (t_cmd *)malloc(sizeof(t_cmd) * (*cmds_cnt));
	if (*cmds == NULL)
		my_error("malloc failed");
	printf("*cmds is %p\n", *cmds);
}

static void	cnt_init(t_cnt *cnt)
{
	cnt->cmd = 0;
	cnt->infile = 0;
	cnt->outfile = 0;
}

static void	alloc_part(t_cmd **cmds, int cmds_index, t_cnt *cnt)
{
	printf("*cmds        is %p\n", *cmds);
	printf("cmds_index   is %d\n", cmds_index);
	printf("cnt->cmd     is %d\n", cnt->cmd);
	printf("cnt->infile  is %d\n", cnt->infile);
	printf("cnt->outfile is %d\n", cnt->outfile);
	(*cmds)[cmds_index].cmd = (char **)malloc(sizeof(char *) * (cnt->cmd + 1));
	printf("here1\n");
	(*cmds)[cmds_index].infile = (char **)malloc(sizeof(char *) * (cnt->infile + 1));
	printf("here2\n");
	(*cmds)[cmds_index].outfile = (char **)malloc(sizeof(char *) * (cnt->outfile + 1));
	printf("here3\n");
}

static void	cmd_part(t_cmd **cmds, t_list *tokens)
{
	int		cmds_index;
	t_cnt	cnt;
	t_list	*current;

#ifdef DEBUG
	printf("***cmd_part***\n");
#endif
	cmds_index = 0;
	cnt_init(&cnt);
	current = tokens;
	while (current != NULL)
	{
		if (ft_strcmp(current->content, "|") == 0)
		{
#ifdef DEBUG
			printf("*** | ***\n");
#endif
			alloc_part(cmds, cmds_index, &cnt);
			cmds_index++;
			cnt_init(&cnt);
		}
		else if (ft_strcmp(current->content, "<") == 0)
		{
#ifdef DEBUG
			printf("*** < ***\n");
#endif
			if (current->next != NULL
				&& ft_strcmp(current->next->content, "|") != 0)
			{
				cnt.infile++;
				current = current->next;
			}
		}
		else if (ft_strcmp(current->content, ">") == 0)
		{
#ifdef DEBUG
			printf("*** > ***\n");
#endif
			if (current->next != NULL
				&& ft_strcmp(current->next->content, "|") != 0)
			{
				cnt.outfile++;
				current = current->next;
			}
		}
		else
		{
#ifdef DEBUG
			printf("*** else ***\n");
#endif
			cnt.cmd++;
		}
		current = current->next;
	}
#ifdef DEBUG
	printf("*** last ***\n");
#endif
	alloc_part(cmds, cmds_index, &cnt);
}

void	cmds_alloc(t_cmd **cmds, int *cmds_cnt, t_list *tokens)
{
#ifdef DEBUG
	printf("***cmds_alloc***\n");
#endif
	cmds_part(cmds, cmds_cnt, tokens);
	cmd_part(cmds, tokens);
}
