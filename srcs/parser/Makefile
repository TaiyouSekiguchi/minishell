# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 10:37:21 by tsekiguc          #+#    #+#              #
#    Updated: 2022/01/14 12:10:15 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSER			=	parser
SRCS			=	parser.c\
					cmds_init.c\
					do_parse.c\
					is_func.c\
					lexer.c\
					my_error.c\
					test_main.c
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
#CFLAGS			+=	-fsanitize=address
INCLUDE			=	-Ilibft
LIB				=	-L../../libft -lft

RM				=	rm -f

.PHONY			:	all clean fclean re

vpath %.h srcs
vpath %.c srcs

all				:	$(PARSER)

$(PARSER)		:	$(OBJS)
					$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(OBJS_DIR)/%.o	:	%.c parser.h
					@[ -d $(OBJS_DIR) ]
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean			:
					$(RM) $(OBJS)

fclean			:
					$(RM) $(OBJS) $(PARSER) 

re				:	fclean all
