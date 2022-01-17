EXPANSION		=	expansion
SRCS			=	expansion.c\
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

all				:	$(EXPANSION)

$(EXPANSION)		:	$(OBJS)
					$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $@

$(OBJS_DIR)/%.o	:	%.c expansion.h
					@[ -d $(OBJS_DIR) ]
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean			:
					$(RM) $(OBJS)

fclean			:
					$(RM) $(OBJS) $(EXPANSION) 

re				:	fclean all
