#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libms.h"

# define NONE_FD (-2)
# define ERROR_FD (-1)
# define READ (0)
# define WRITE (1)
# define CHILD 0

# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define SYNTAX_ERROR_MSG "syntax error near unexpected token 'newline'"

typedef enum e_boolean
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

typedef enum e_quote
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

typedef struct s_cmd_info
{
	t_list	*cmd;
	t_list	*redirect;
}				t_cmd_info;

typedef struct s_dir
{
	char	*pwd;
	char	*old_pwd;
	char	**my_env;
}				t_dir;

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	heredoc;
}				t_fd;

//Main
void		init(t_dir *d_info);
void		main_free(t_dir *info);
void		do_process_free(t_list **token_list, t_list **cmd_info_list);
void		do_process(char *input, t_dir *d_info);
//readline
char		*ms_rl_gets(void);
//utils
int			get_environ_row(char **environ);
void		call_export(char *env_name, char *value, char ***my_env);
void		call_unset(char *env_name, char ***my_env);
void		put_error_exit(char *name, char *msg, t_boolean is_exit);
int			get_g_status(void);
void		set_g_status(long num);
void		set_g_status_exception(int num);
void		sigint_handler(int signum);
void		default_signal(void);
t_list		*split_lst(char *str, char c);
//lexer
void		lexer(t_list **list, char *cmd);
int			is_quote(char c);
int			is_blank(char c);
int			is_delimiter(char c);
int			is_metachar(char c);
int			is_redirect(char c1, char c2);
int			is_heredoc(char *token);
int			is_name(char c);
t_quote		quote_set(char c, t_quote quote);
//parser
void		parser(t_list **cmds, t_list *tokens);
int			syntax_check(t_list *tokens);
int			token_kind(char *token);
//expander
void		expander(t_list *cmds, char **my_env);
t_list		*expand_cmd_info_element(t_list *list, char **my_env);
t_list		*expand(char *token, char **my_env);
char		*expand_for_heredoc(char *token, char **my_env);
char		*ms_getenv(char **my_env, char *key);
char		*remove_quotation(char *token);
char		*get_val_name(char *token);
char		*expand_g_status(char **token);
char		*expand_num(char **token);
char		*expand_from_env(char **token, char **my_env);

//executer
void		executer(t_list *cmds, t_dir *d_info);
pid_t		do_cmd(t_cmd_info *cmd_info, t_boolean is_last, t_dir *d_info);
void		do_exec(t_cmd_info *cmd_info, t_dir *d_info);
int			infile_open(char *token);
int			heredoc_open(char *token, char **my_env);
int			outfile_open(char *token);
int			append_open(char *token);
void		get_redirect_fd(t_list *redirect, char **my_env, t_fd *redirect_fd);
char		*cmd_path_search(char *cmd_name, char **my_env);
void		stdin_reset(void);
char		*set_tmp_file_name(void);
int			tmp_file_create(char *tmp_file_name);
int			tmp_file_open(char *tmp_file_name);
void		tty_reset(void);
void		do_redirect(t_fd *redirect_fd);

//builtin
int			is_builtin(char *cmd_name);
int			do_builtin(char *cmd, int argc, char *argv[], t_dir *d_info);
int			builtin_echo(int argc, char *argv[]);
int			builtin_cd(int argc, char *argv[], t_dir *d_info);
char		*rewrite_absolute_path(t_list *dir_lst, char *input_path);
char		*rewrite_relative_path(t_list *dir_lst, char *pwd);
int			builtin_export(int argc, char *argv[], char ***environ);
char		*get_key(char *key_value, t_boolean *is_append);
void		export_new_word(char ***environ, char *key_value,
				t_boolean is_append);
void		export_exist_word(char ***environ, int index, char *key_value);
int			builtin_unset(int argc, char *argv[], char ***environ);
int			builtin_pwd(t_dir *d_info);
int			builtin_env(char **environ);
int			builtin_exit(int argc, char *argv[]);

#endif
