#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include "../../../libft/libft.h"

#define DEBUG 1



typedef	struct s_cmd
{
	char	**cmd;
	char	**infile;
	char	**outfile;
}				t_cmd;

typedef struct s_cnt
{
	int		cmd;
	int		infile;
	int		outfile;
}				t_cnt;

typedef struct s_index
{
	int		cmds;
	int		cmd;
	int		infile;
	int		outfile;
}				t_index;

void	parser(t_cmd **cmds, int *cmds_cnt, t_list *tokens);
void	cmds_alloc(t_cmd **cmds, int *cmds_cnt, t_list *tokens);
void	do_parse(t_cmd **cmds, t_list *tokens);
void	my_error(char *msg);


#endif
