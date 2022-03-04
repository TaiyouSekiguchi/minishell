/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:57:09 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/04 16:22:59 by yjimpei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strappend(char *body, char *add)
{
	char	*new;
	size_t	len;

	if (body == NULL || add == NULL)
		return (NULL);
	len = ms_strlen(body) + ms_strlen(add);
	new = (char *)ms_xmalloc(sizeof(char) * (len + 1));
	new = ms_strcpy(new, body);
	new = ms_strcat(new, add);
	free(body);
	free(add);
	return (new);
}
