#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libms.h"

# define NONE_FD (-2)
# define ERROR_FD (-1)
# define READ (0)
# define WRITE (1)

# define COMMAND_NOT_FOUND 127
# define PERMISSION_DENIED 126

# define SYNTAX_ERROR_MSG "syntax error near unexpected token 'newline'"

# define CHILD 0


int	g_status;

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

typedef	struct s_cmd_info
{
	t_list	*cmd;
	t_list	*infile;
	t_list	*outfile;
}				t_cmd_info;

typedef struct s_dir
{
	char	*pwd;
	char	*old_pwd;
}				t_dir;

//readline
char		*rl_gets(void);
//utils
void		init_dir_info(t_dir *d_info);
void		init_shlvl(void);
void		call_export(char *env_name, char *value);
void		put_error_exit(char *name, int status, char *msg, t_boolean is_exit);
//lexer
void		lexer(t_list **list, char *cmd);
int			is_quote(char c);
int			is_blank(char c);
int			is_delimiter(char c);
int			is_metachar(char c);
int			is_redirect(char c1, char c2);
int			is_heredoc(char *token);
t_quote		quote_set(char c, t_quote quote);
//parser
void		parser(t_list **cmds, t_list *tokens);
int			syntax_check(t_list *tokens);
int			token_kind(char *token);
//expander
void		expander(t_list *cmds);
char		*expand(char *token, t_boolean in_heredoc);
char		*search_environ(char *name);
char		*remove_quotation(char *token);
//executer
void		executer(t_list *cmds, t_dir *d_info);
void		do_exec(t_cmd_info *cmd_info, t_dir *d_info);
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
int			do_builtin(char *cmd, int argc, char *argv[], t_dir *d_info);
int			builtin_echo(int argc, char *argv[]);
int			builtin_cd(int argc, char *argv[], t_dir *d_info);
int			builtin_export(int argc, char *argv[]);
int			builtin_unset(int argc, char *argv[]);
int			builtin_pwd(t_dir *d_info);
int			builtin_env(void);
int			builtin_exit(int argc, char *argv[]);

#endif
