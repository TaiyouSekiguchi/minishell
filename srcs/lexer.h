/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:18:44 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/06 23:43:28 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include "../libft/libft.h"

typedef	enum e_boolean
{
	TRUE = 1,
	FALSE = 0,
}			t_boolean;

typedef	enum e_quote_io
{
	IN,
	OUT,
	NONE,
}			t_quote_io;

void	*lexer(t_list **list, char *cmd);

#endif
