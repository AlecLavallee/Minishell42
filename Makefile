# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 11:56:39 by alelaval          #+#    #+#              #
#    Updated: 2022/07/25 18:12:44 by alelaval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./srcs/parser/paths.c \
		./srcs/process/process.c \
		./srcs/utils/utils.c \
		./srcs/utils/utils2.c \
		./srcs/utils/utils3.c \
		./srcs/pipex.c

OBJS =	${SRCS:.c=.o}

CC 	= gcc

INCLUDE =	./headers/
CFLAGS =	-Wall -Wextra -Werror
RM = 		rm -rf

all: 		${NAME}

bonus:		pipex_bonus

.c.o:
			${CC} ${CFLAGS} -I${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -I${INCLUDE} -o ${NAME} ${OBJS}

${NAME_BONUS}:	${OBJS}
					${CC} ${CFLAGS} -I${INCLUDE} -o ${NAME_BONUS} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:	clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		bonus all clean fclean re