/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:51 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 16:48:28 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

t_list	*ms_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*ret;
	t_list	*new;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	ret = NULL;
	current = lst;
	while (current != NULL)
	{
		new = ms_lstnew((*f)(current->content));
		if (new == NULL)
		{
			ms_lstclear(&ret, (*del));
			return (NULL);
		}
		ms_lstadd_back(&ret, new);
		current = current->next;
	}
	return (ret);
}
