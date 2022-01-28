/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:12:49 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/28 14:12:51 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_environ(char *key)
{
	extern char		**environ;
	char			*ret;
	int				row;
	char			**split;

	row = 0;
	while (environ[row] != NULL)
	{
		split = ms_split(environ[row], '=');
		if (ms_strcmp(split[0], key) == 0)
		{
			ret = ms_strdup(split[1]);
			ms_split_free(split);
			return (ret);
		}
		ms_split_free(split);
		row++;
	}
	return (ms_strdup(""));
}
