/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:10:42 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/06 17:44:06 by yjimpei          ###   ########.fr       */
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
			if (current->next == NULL || token_kind(current->next->content) != CMD)
			{
				put_error_exit(NULL, g_status, SYNTAX_ERROR_MSG, FALSE);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
