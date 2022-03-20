/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_kind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:30:00 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/20 17:28:12 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_kind(char *token)
{
	if (ms_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ms_strcmp(token, "<") == 0)
		return (INFILE);
	else if (ms_strcmp(token, ">") == 0)
		return (OUTFILE);
	else if (ms_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ms_strcmp(token, ">>") == 0)
		return (APPEND);
	else
		return (CMD);
}
