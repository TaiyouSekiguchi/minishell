/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:05:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/04 16:41:22 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "get_next_line.h"
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
	NOT_BUILTIN,
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
void		lexer(t_list **list, char *cmd);
int			is_quote(char c);
int			is_blank(char c);
int			is_delimiter(char c);
int			is_metachar(char c);
int			is_redirect(char c1, char c2);
void		quote_set(char c, t_quote *quote);

//parser
void		parser(t_list **cmds, t_list *tokens);
int			syntax_check(t_list *tokens);
int			token_kind(char *token);

//expander
void		expander(t_list *cmds);
void		expand(char **token);
char		*search_environ(char *name);
char		*remove_quotation(char *token);

//executer
void		executer(t_list *cmds);
void		do_exec(t_cmd *cmd);
void		do_redirect(char *tmp, t_kind kind);
void		do_pipe(t_list *cmds);

//builtin
int			is_builtin(char *cmd_name);
void		do_builtin(char *cmd, int argc, char *argv[]);
void		builtin_echo(int argc, char *argv[]);
void		builtin_cd(int argc, char *argv[]);
void		builtin_export(int argc, char *argv[]);
void		builtin_unset(int argc, char *argv[]);
void		builtin_pwd(int act);
void		builtin_env(void);
void		builtin_exit(int argc, char *argv[]);

#endif
