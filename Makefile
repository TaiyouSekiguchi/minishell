# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 17:03:08 by tsekiguc          #+#    #+#              #
#    Updated: 2022/01/08 10:53:24 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL		=	minishell
SRCS			=	main.c
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDE			=	-Ilibft
LIB				=	-lreadline -Llibft -lft

RM				=	rm -f

.PHONY			:	all clean fclean re

vpath %.h srcs
vpath %.c srcs

all				:	$(MINISHELL)

$(MINISHELL)	:	$(OBJS)
					$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(OBJS_DIR)/%.o	:	%.c minishell.h
					@[ -d $(OBJS_DIR) ]
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean			:
					$(RM) $(OBJS)

fclean			:
					$(RM) $(OBJS) $(MINISHELL) 

re				:	fclean all
