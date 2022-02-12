CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
INCLUDE					=	-I includes -I ${shell brew --prefix readline}/include
READLINE_LIB			=	-l readline -L ${shell brew --prefix readline}/lib
LIBMS					=	./lib/libms/libms.a
SRCS_DIR				=	$(dir $(SRCS))\
							${dir ${UTILS_SRCS}}\
							${dir ${READLINE_SRCS}}\
							${dir ${LEXER_SRCS}}\
							${dir ${PARSER_SRCS}}\
							${dir ${EXPANDER_SRCS}}\
							${dir ${BUILTIN_SRCS}}\
							${dir ${EXECUTER_SRCS}}
OBJS_DIR				=	./objs
BINDIRS					=	${addprefix ${OBJS_DIR}/, ${SRCS_DIR}}

############ minishell #############
MINISHELL				=	minishell
SRCS					=	srcs/main.c
OBJS					=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
#####################################

############### test  ###############
ALL_IN_TEST				=	all_in_test
READLINE_TEST			=	readline_test
LEXER_TEST				=	lexer_test
PARSER_TEST				=	parser_test
EXPANDER_TEST			=	expander_test
EXECUTER_TEST			=	executer_test

ALL_IN_TEST_SRCS		=	srcs/all_in_test.c
READLINE_TEST_SRCS		=	srcs/readline/readline_test.c
LEXER_TEST_SRCS			=	srcs/lexer/lexer_test.c
PARSER_TEST_SRCS		=	srcs/parser/parser_test.c
EXPANDER_TEST_SRCS		=	srcs/expander/expander_test.c
EXECUTER_TEST_SRCS		=	srcs/executer/executer_test.c

ALL_IN_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(ALL_IN_TEST_SRCS:.c=.o))
READLINE_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(READLINE_TEST_SRCS:.c=.o))
LEXER_TEST_OBJS			=	$(addprefix $(OBJS_DIR)/, $(LEXER_TEST_SRCS:.c=.o))
PARSER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(PARSER_TEST_SRCS:.c=.o))
EXPANDER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(EXPANDER_TEST_SRCS:.c=.o))
EXECUTER_TEST_OBJS		=	$(addprefix $(OBJS_DIR)/, $(EXECUTER_TEST_SRCS:.c=.o))
#####################################

########### utils ############
UTILS_SRCS				=	srcs/utils/is_func.c\
							srcs/utils/quote_set.c\
							srcs/utils/get_next_line.c\
							srcs/utils/get_next_line_utils.c\
							srcs/utils/search_environ.c \
							srcs/utils/remove_quotation.c
UTILS_OBJS				=	$(addprefix $(OBJS_DIR)/, $(UTILS_SRCS:.c=.o))
#####################################

############ readline #############
READLINE_SRCS			=	srcs/readline/readline.c
READLINE_OBJS			=	$(addprefix $(OBJS_DIR)/, $(READLINE_SRCS:.c=.o))
#####################################

############ lexer #############
LEXER_SRCS				=	srcs/lexer/lexer.c
LEXER_OBJS				=	$(addprefix $(OBJS_DIR)/, $(LEXER_SRCS:.c=.o))
#####################################

############ parser #############
PARSER_SRCS				=	srcs/parser/parser.c\
							srcs/parser/syntax_check.c\
							srcs/parser/token_kind.c
PARSER_OBJS				=	$(addprefix $(OBJS_DIR)/, $(PARSER_SRCS:.c=.o))
#####################################

############ expander #############
EXPANDER_SRCS			=	srcs/expander/expander.c\
							srcs/expander/expand.c
EXPANDER_OBJS			=	$(addprefix $(OBJS_DIR)/, $(EXPANDER_SRCS:.c=.o))
########################################

######## builtin ##########
BUILTIN_SRCS			=	srcs/builtin/builtin.c\
							srcs/builtin/builtin_echo.c\
							srcs/builtin/builtin_cd.c\
							srcs/builtin/builtin_pwd.c\
							srcs/builtin/builtin_env.c\
							srcs/builtin/builtin_export.c\
							srcs/builtin/builtin_unset.c\
							srcs/builtin/builtin_exit.c
BUILTIN_OBJS			=	$(addprefix $(OBJS_DIR)/, $(BUILTIN_SRCS:.c=.o))
########################################

############ executer #############
EXECUTER_SRCS			=	srcs/executer/executer.c\
							srcs/executer/do_pipe.c\
							srcs/executer/do_redirect.c\
							srcs/executer/do_exec.c
EXECUTER_OBJS		=	$(addprefix $(OBJS_DIR)/, $(EXECUTER_SRCS:.c=.o))
########################################

.PHONY			:	all clean fclean re tclean tfclean

all					:	$(MINISHELL)

$(MINISHELL)		:	$(OBJS) $(READLINE_OBJS) $(UTILS_OBJS) $(LIBMS) $(LEXER_OBJS) $(BUILTIN_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTER_OBJS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(READLINE_TEST)	:	$(READLINE_TEST_OBJS) $(READLINE_OBJS) $(LIBMS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(LEXER_TEST)		:	$(LEXER_TEST_OBJS) $(LEXER_OBJS) $(UTILS_OBJS) $(LIBMS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(PARSER_TEST)		:	$(PARSER_TEST_OBJS) $(PARSER_OBJS) $(LEXER_OBJS) $(UTILS_OBJS) $(LIBMS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(EXPANDER_TEST)	:	$(EXPANDER_TEST_OBJS) $(EXPANDER_OBJS) $(PARSER_OBJS) $(LEXER_OBJS) $(UTILS_OBJS) $(LIBMS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(EXECUTER_TEST)	:	$(EXECUTER_TEST_OBJS) $(EXECUTER_OBJS) $(BUILTIN_OBJS)\
						$(EXPANDER_OBJS) $(PARSER_OBJS) $(LEXER_OBJS) $(UTILS_OBJS) $(LIBMS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(ALL_IN_TEST)		:	$(ALL_IN_TEST_OBJS) $(READLINE_OBJS) $(UTILS_OBJS) $(LIBMS) $(LEXER_OBJS) $(BUILTIN_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTER_OBJS)
						$(CC) -g $(CFLAGS) $^ $(INCLUDE) -o $@ $(READLINE_LIB)

$(OBJS_DIR)/%.o		:	%.c
						@mkdir -p ${BINDIRS}
						$(CC) -g $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBMS)			:
						$(MAKE) -C ./lib/libms

clean				:	tclean
						$(MAKE) fclean -C ./lib/libms
						$(RM) -r $(OBJS_DIR)

fclean				: clean tfclean
						$(RM) $(OBJS) $(MINISHELL)

re					:	fclean all

tclean				:
						$(RM)\
						$(READLINE_TEST_OBJS)\
						$(LEXER_TEST_OBJS)\
						$(PARSER_TEST_OBJS)\
						$(EXPANDER_TEST_OBJS)\
						$(EXECUTER_TEST_OBJS)\
						$(ALL_IN_TEST_OBJS)

tfclean				:
						$(RM) $(READLINE_TEST_OBJS) $(READLINE_TEST) $(LEXER_TEST_OBJS) $(LEXER_TEST) $(PARSER_TEST_OBJS) $(PARSER_TEST) $(EXPANDER_TEST) $(EXPANDER_TEST_OBJS) $(EXECUTER_TEST) $(EXECUTER_TEST_OBJS) $(ALL_IN_TEST) $(ALL_IN_TEST_OBJS)
