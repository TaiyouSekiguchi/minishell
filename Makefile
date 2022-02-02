# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 17:33:29 by tsekiguc          #+#    #+#              #
#    Updated: 2022/02/02 13:53:52 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
INCLUDE					=	-Ilibms -I/usr/local/opt/readline/include
LIB						=	-lreadline -Llibms -lms -L/usr/local/opt/readline/lib
RM						=	rm -f

############ minishell #############
MINISHELL				=	minishell
SRCS					=

OBJS_DIR				=	./objs
OBJS					=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
#####################################


############ readline  #############
READLINE_TEST			=	readline_test
READLINE_TEST_SRCS		=	readline_test.c

OBJS_DIR				=	./objs
READLINE_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(READLINE_TEST_SRCS:.c=.o))
#####################################


############ lexer test #############
LEXER_TEST				=	lexer_test
LEXER_TEST_SRCS			=	lexer.c\
							is_func.c\
							quote_set.c\
							lexer_test.c

LEXER_TEST_OBJS			=	$(addprefix $(OBJS_DIR)/, $(LEXER_TEST_SRCS:.c=.o))
#####################################


############ parser test #############
PARSER_TEST				=	parser_test
PARSER_TEST_SRCS		=	lexer.c\
							is_func.c\
							quote_set.c\
							parser.c\
							syntax_check.c\
							token_kind.c\
							parser_test.c

PARSER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(PARSER_TEST_SRCS:.c=.o))
#####################################


############ expander test #############
EXPANDER_TEST			=	expander_test
EXPANDER_TEST_SRCS		=	lexer.c\
							is_func.c\
							quote_set.c\
							parser.c\
							syntax_check.c\
							token_kind.c\
							expander.c\
							expand.c\
							remove_quotation.c\
							expander_test.c

EXPANDER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(EXPANDER_TEST_SRCS:.c=.o))
########################################


############ executer test #############
EXECUTER_TEST			=	executer_test
EXECUTER_TEST_SRCS		=	lexer.c\
							is_func.c\
							quote_set.c\
							parser.c\
							syntax_check.c\
							token_kind.c\
							expander.c\
							expand.c\
							search_environ.c\
							remove_quotation.c\
							executer.c\
							get_next_line.c\
							get_next_line_utils.c\
							builtin_echo.c\
							builtin_cd.c\
							builtin_pwd.c\
							builtin_env.c\
							builtin_export.c\
							builtin_unset.c\
							builtin_exit.c\
							executer_test.c

EXECUTER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(EXECUTER_TEST_SRCS:.c=.o))
########################################






.PHONY			:	all clean fclean re tclean tfclean

vpath %.h srcs
vpath %.c srcs

all					:	$(MINISHELL)

$(MINISHELL)		:	$(OBJS)
						$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(READLINE_TEST)	:	$(READLINE_TEST_OBJS)
						$(CC) $(READLINE_TEST_OBJS) $(CFLAGS) $(LIB) -o $@

$(LEXER_TEST)		:	$(LEXER_TEST_OBJS)
						$(CC) $(LEXER_TEST_OBJS) $(CFLAGS) $(LIB) -o $@

$(PARSER_TEST)		:	$(PARSER_TEST_OBJS)
						$(CC) $(PARSER_TEST_OBJS) $(CFLAGS) $(LIB) -o $@

$(EXPANDER_TEST)	:	$(EXPANDER_TEST_OBJS)
						$(CC) $(EXPANDER_TEST_OBJS) $(CFLAGS) $(LIB) -o $@

$(EXECUTER_TEST)	:	$(EXECUTER_TEST_OBJS)
						$(CC) $(EXECUTER_TEST_OBJS) $(CFLAGS) $(LIB) -o $@


$(OBJS_DIR)/%.o		:	%.c
						@[ -d $(OBJS_DIR) ]
						$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean				:
						$(RM) $(OBJS)

fclean				:
						$(RM) $(OBJS) $(MINISHELL)

re					:	fclean all

tclean				:
						$(RM)\
						$(READLINE_TEST_OBJS)\
						$(LEXER_TEST_OBJS)\
						$(PARSER_TEST_OBJS)\
						$(EXPANDER_TEST_OBJS)\
						$(EXECUTER_TEST_OBJS)

tfclean				:
						$(RM) $(READLINE_TEST_OBJS) $(READLINE_TEST) $(LEXER_TEST_OBJS) $(LEXER_TEST) $(PARSER_TEST_OBJS) $(PARSER_TEST) $(EXPANDER_TEST) $(EXPANDER_TEST_OBJS) $(EXECUTER_TEST) $(EXECUTER_TEST_OBJS)

