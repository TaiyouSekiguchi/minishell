/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:05:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/01/29 18:06:14 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../libms/libms.h"

typedef	enum e_boolean
{
	TRUE = 1,
	FALSE = 0,
}			t_boolean;

typedef enum e_io
{
	STDIN = 0,
	STDOUT,
	STDERR,
}			t_io;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NO_BUILTIN,
}			t_builtin;

typedef	enum e_quote
{
	SINGLE,
	DOUBLE,
	NONE,
}			t_quote;

typedef enum e_kind
{
	CMD = 0,
	PIPE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
}			t_kind;

typedef	struct s_cmd
{
	t_list	*cmd;
	t_list	*infile;
	t_list	*outfile;
}				t_cmd;


//lexer
void	lexer(t_list **list, char *cmd);
int		is_quote(char c);
int		is_blank(char c);
int		is_delimiter(char c);
int		is_metachar(char c);
int		is_redirect(char c1, char c2);
void	quote_set(char c, t_quote *quote);

//parser
void	parser(t_list **cmds, t_list *tokens);
int		syntax_check(t_list *tokens);
int		token_kind(char *token);

//expander
void	expander(t_list *cmds);
void	expand(char **token);
char	*search_environ(char *name);
char	*remove_quotation(char *token);

//executer
void	executer(t_list *cmds);

//builtin
void	echo(int argc, char *argv[]);
void	cd(int argc, char *argv[]);
void	export(int argc, char *argv[]);
void	unset(int argc, char *argv[]);

void	pwd(void);
void	env(void);

#endif
