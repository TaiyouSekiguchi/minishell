/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:24:24 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/27 16:36:47 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*absolute_path;

	absolute_path = getcwd(NULL, 0);
	if (absolute_path == NULL)
		return ;
	ms_putendl_fd(absolute_path, STDOUT);
	free(absolute_path);
}
