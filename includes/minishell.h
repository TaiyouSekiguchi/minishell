/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:05:58 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/17 21:07:12 by tsekiguc         ###   ########.fr       */
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

#include "libms.h"

# define NONE_FD (-1)
# define READ (0)
# define WRITE (1)

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

//readline
char	*rl_gets(void);

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
void		do_redirect(int infile_fd, int outfile_fd);
void		do_pipe(t_list *cmds, int fd);
int			infile_open(char *token);
void		heredoc_loop(int fd, char *token);
int			heredoc_open(char *token);
int			outfile_open(char *token);
int			append_open(char *token);
int			redirect_file_open(char *token);
int			get_redirect_fd(t_list *token_list);
void		do_redirect(int infile_fd, int outfile_fd);
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
