# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 17:03:08 by tsekiguc          #+#    #+#              #
#    Updated: 2021/12/29 17:32:55 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL		=	minishell
SRCS			=	main.c
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	-lreadline

RM				=	rm -f

.PHONY			:	all clean fclean re

vpath %.c srcs

all				:	$(MINISHELL)

$(MINISHELL)	:	$(OBJS)
					$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(OBJS_DIR)/%.o	:	%.c ./srcs/minishell.h
					@[ -d $(OBJS_DIR) ]
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					$(RM) $(OBJS)

fclean			:
					$(RM) $(OBJS) $(MINISHELL) 

re				:	fclean all
