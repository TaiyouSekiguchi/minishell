/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:41:38 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/14 11:14:38 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_cmd **cmds, int *cmds_cnt, t_list *tokens)
{

#ifdef DEBUG
	printf("**************parser*****************\n");
#endif

	cmds_alloc(cmds, cmds_cnt, tokens);
	do_parse(cmds, tokens);


#ifdef DEBUG
	printf("**************parser*****************\n");
#endif

}
