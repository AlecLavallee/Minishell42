# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 12:35:48 by msuji             #+#    #+#              #
#    Updated: 2022/08/01 12:35:49 by msuji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRCS	=	./parsing/minishell.c	\
			./parsing/outil_signal.c		\
			./parsing/error.c 				\
			./parsing/outil_lexer.c			\
			./parsing/quoting.c 			\
			./parsing/lexer.c 				\
			./parsing/get_command_line.c \
			./parsing/split_token.c 	\
			./parsing/outil.c			\
			./parsing/expension.c		\
	


OBJS	=	$(SRCS:.c=.o)

HEADER	=	./inc/

LIBFT	=	./libft/

LIBFT_A	=	./libft/libft.a

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address #-fsanitize=leak

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
			@make -C $(LIBFT)
			ar rcs $(LIBFT_A) $(OBJS)
			ranlib $(LIBFT_A)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		$(RM) $(OBJS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re