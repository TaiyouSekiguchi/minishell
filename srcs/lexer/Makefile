# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 17:03:08 by tsekiguc          #+#    #+#              #
#    Updated: 2022/01/14 10:51:11 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEXER			=	lexer
SRCS			=	lexer.c\
					is_func.c\
					test_main.c
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDE			=	-Ilibft
LIB				=	-L../../libft -lft

RM				=	rm -f

.PHONY			:	all clean fclean re

vpath %.h srcs
vpath %.c srcs

all				:	$(LEXER)

$(LEXER)		:	$(OBJS)
					$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(OBJS_DIR)/%.o	:	%.c lexer.h
					@[ -d $(OBJS_DIR) ]
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean			:
					$(RM) $(OBJS)

fclean			:
					$(RM) $(OBJS) $(LEXER) 

re				:	fclean all
