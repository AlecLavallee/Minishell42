NAME	=	parsing_test

SRCS	=	../../parsing/outil_signal.c		\
			../../parsing/error.c 				\
			../../parsing/outil_lexer.c			\
			../../parsing/quoting.c 			\
			../../parsing/lexer.c 				\
			../../parsing/get_command_line.c \
			../../parsing/split_token.c 	\
			../../parsing/outil.c			\
			../../parsing/expension.c		\
			../../parsing/parser.c			\
			../../parsing/outil_parser.c	\
			./tester_parser_minishell.c					\


OBJS	=	$(SRCS:.c=.o)

HEADER	=	../../inc/

LIBFT	=	../../libft/

LIBFT_A	=	../../libft/libft.a

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address -fsanitize=leak

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
