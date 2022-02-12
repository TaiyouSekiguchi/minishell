/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:10:42 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 18:03:42 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_check(t_list	*tokens)
{
	t_list	*current;

	current = tokens;
	while (current != NULL)
	{
		if (token_kind(current->content) != CMD)
		{
			if (current->next == NULL)
			{
				printf("syntax error new line\n");
				return (0);
			}
			else if (token_kind(current->next->content) != CMD)
			{
				printf("syntax error\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
