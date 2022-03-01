# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:12 by tsekiguc          #+#    #+#              #
#    Updated: 2022/03/01 18:01:04 by yjimpei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libms.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	ms_atoi.c\
			ms_bzero.c\
			ms_calloc.c\
			ms_int_check.c\
			ms_isalnum.c\
			ms_isalpha.c\
			ms_isascii.c\
			ms_isdigit.c\
			ms_isprint.c\
			ms_isspace.c\
			ms_itoa.c\
			ms_lstadd_back.c\
			ms_lstadd_front.c\
			ms_lstclear.c\
			ms_lstdelone.c\
			ms_lstiter.c\
			ms_lstlast.c\
			ms_lstmap.c\
			ms_lstnew.c\
			ms_lstsize.c\
			ms_memccpy.c\
			ms_memchr.c\
			ms_memcmp.c\
			ms_memcpy.c\
			ms_memmove.c\
			ms_memset.c\
			ms_putchar_fd.c\
			ms_putendl_fd.c\
			ms_putnbr_fd.c\
			ms_putstr_fd.c\
			ms_split.c\
			ms_strchr.c\
			ms_strcmp.c\
			ms_strdup.c\
			ms_strndup.c\
			ms_striteri.c\
			ms_strjoin.c\
			ms_strlcat.c\
			ms_strlcpy.c\
			ms_strlen.c\
			ms_strmapi.c\
			ms_strncmp.c\
			ms_strnstr.c\
			ms_strrchr.c\
			ms_strtrim.c\
			ms_substr.c\
			ms_tolower.c\
			ms_toupper.c\
			ms_error.c\
			ms_xmalloc.c\
			ms_strcpy.c\
			ms_strcat.c\
			ms_strappend.c\
			ms_split_free.c\
			ms_isnum_string.c

OBJS	=	$(SRCS:.c=.o)

.SUFFIXES:
.SUFFIXES:	.c .o

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			ar rc $@ $?
			ranlib $@

%.o		:	%.c libms.h
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all
