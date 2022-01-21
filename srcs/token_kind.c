/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_kind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:30:00 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/21 18:04:14 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_kind(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (INFILE);
	else if (ft_strcmp(token, ">") == 0)
		return (OUTFILE);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	else
		return (CMD);
}
