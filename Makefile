SRCS	= main.c philo_utils.c ft_atouli.c list_utils.c create_philos.c \
		routine.c

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
				${RM} ${OBJBS} ${OBJS}

fclean: 	clean
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re