/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:18:44 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/08 11:32:23 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include "../../../libft/libft.h"

typedef	enum e_boolean
{
	TRUE = 1,
	FALSE = 0,
}			t_boolean;

typedef	enum e_quote
{
	SINGLE,
	DOUBLE,
	NONE,
}			t_quote;

void	lexer(t_list **list, char *cmd);
int		is_blank(char c);
int		is_delimiter(char c);
int		is_metachar(char c);
int		is_redirect(char c1, char c2);



#endif
