/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:57:09 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/24 16:29:37 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_strappend(char **body, char *add)
{
	char	*new;
	size_t	len;

	if (body == NULL || *body == NULL || add == NULL)
		return ;
	len = ms_strlen(*body) + ms_strlen(add);
	new = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	ms_strcpy(&new, *body);
	ms_strcat(&new, add);
	free(*body);
	*body = new;
}
