NAME = pipex

SRCS = srcs/ft_split.c srcs/ft_strdup.c srcs/ft_strlcat.c srcs/main.c srcs/tools.c srcs/free.c srcs/fork.c srcs/check_err.c srcs/path.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all:	$(NAME)

$(NAME): ${OBJS}
	$(CC) -o $(NAME) $(CFLAGS) ${OBJS}

clean:
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
