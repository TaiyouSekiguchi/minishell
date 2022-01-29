/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:45:53 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/29 17:51:35 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
get_index_of_name_in_environ(char *name)
{
	extern char		**environ;
	char			**split;
	char			*env_name;
	char			*env_value;
	int				index;
	size_t			i;

	index = -1;
	split = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ms_split(environ[i], '=');
		env_name = split[0];
		env_value = split[1];
		if (ms_strcmp(env_name, name) == 0)
		{
			index = i;
			break ;
		}
		i++;
		ms_split_free(split);
	}
	//ms_split_free(split);
	return (index);
}

char
*get_variable_name(char *argv)
{
	char	**split;
	char	*name;

	split = ms_split(argv, '=');
	name = ms_strdup(split[0]);
	ms_split_free(split);
	return (name);
}


int
count_environ_variable(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	return (i);
}

void
export(int argc, char *argv[])
{
	extern char	**environ;
	char	*name;
	int		index;

	int		len;
	char	**new_env;
	int		i;

	if (argc == 1)
		return ;

	name = get_variable_name(argv[1]);
	index = get_index_of_name_in_environ(name);
	if (index == -1)
	{
		len = count_environ_variable();
		new_env = (char **)ms_xmalloc(sizeof(char *) * (len + 1 + 1));
		i = 0;
		while (environ[i] != NULL)
		{
			new_env[i] = environ[i];
			i++;
		}
		new_env[i] = ms_strdup(argv[1]);
		i++;
		new_env[i] = NULL;
		//free(environ)???
		environ = new_env;
	}
	else
	{
		free(environ[index]);
		environ[index] = ms_strdup(argv[1]);
	}
}
