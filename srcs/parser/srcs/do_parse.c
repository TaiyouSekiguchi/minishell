/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:43:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/14 12:09:01 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	index_init(t_index *index)
{
	index->cmds = 0;
	index->cmd = 0;
	index->infile = 0;
	index->outfile = 0;
}

static void	index_reset(t_index *index)
{
	index->cmds++;
	index->cmd = 0;
	index->infile = 0;
	index->outfile = 0;
}

static void	null_terminate(t_cmd **cmds, t_index *index)
{
	(*cmds)[index->cmds].cmd[index->cmd] = NULL;
	(*cmds)[index->cmds].infile[index->infile] = NULL;
	(*cmds)[index->cmds].outfile[index->outfile] = NULL;
}

void	do_parse(t_cmd **cmds, t_list *tokens)
{
	t_index		index;
	t_list		*current;

#ifdef DEBUG
	printf("***do_parse***\n");
#endif

	index_init(&index);
	current = tokens;
	while (current != NULL)
	{
		if (ft_strcmp(current->content, "|") == 0)
		{
			printf("*** | ***\n");
			null_terminate(cmds, &index);
			index_reset(&index);
		}
		else if (ft_strcmp(current->content, "<") == 0)
		{
			printf("*** < ***\n");
			if (current->next != NULL
				&& ft_strcmp(current->next->content, "|") != 0)
			{
				current = current->next;
				(*cmds)[index.cmds].infile[index.infile] = ft_strdup(current->content);
				index.infile++;
			}
		}
		else if (ft_strcmp(current->content, ">") == 0)
		{
			printf("*** > ***\n");
			if (current->next != NULL
				&& ft_strcmp(current->next->content, "|") != 0)
			{
				current = current->next;
				(*cmds)[index.cmds].outfile[index.outfile] = ft_strdup(current->content);
				index.outfile++;
			}
		}
		else
		{
			printf("*** else ***\n");
			(*cmds)[index.cmds].cmd[index.cmd] = ft_strdup(current->content);
			index.cmd++;
		}
		current = current->next;
	}
	null_terminate(cmds, &index);
}
