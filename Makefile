SRCS	= test.c

OBJS 	= ${SRCS:.c=.o}

NAME	= res.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o: %.c
			$(CC) -Wall -Wextra -Werror -Imlx -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
			$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
