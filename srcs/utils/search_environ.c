/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:12:49 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/08 17:07:36 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i] != NULL)
	{
		ms_putendl_fd(my_env[i], STDOUT);
		i++;
	}
}

char	*search_environ(char **my_env, char *name)
{
	char	*ret;
	int		row;
	char	**split;

	//env_print(my_env);
	row = 0;
	while (my_env[row] != NULL)
	{
		printf("my_env[%d] : %s\n", row, my_env[row]);
		split = ms_split(my_env[row], '=');
		if (ms_strcmp(split[0], name) == 0)
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
