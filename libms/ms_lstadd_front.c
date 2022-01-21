/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:47 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 16:12:22 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*new_last;
	t_list	*old_top;

	if (lst == NULL || new == NULL)
		return ;
	old_top = *lst;
	new_last = ms_lstlast(new);
	old_top->prev = new_last;
	new_last->next = old_top;
	*lst = new;
}
