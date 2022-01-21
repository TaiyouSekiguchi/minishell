/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:52 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 16:04:50 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

t_list	*ms_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)ms_xmalloc(sizeof(t_list));
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
