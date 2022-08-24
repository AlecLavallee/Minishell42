# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 12:35:48 by msuji             #+#    #+#              #
#    Updated: 2022/08/24 11:46:45 by msuji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRCS	=	./srcs/main/minishell.c	\
			./srcs/main/outil_main.c	\
			./srcs/signal/signal_init.c		\
			./srcs/signal/signal_exec.c			\
			./srcs/parsing/error.c 				\
			./srcs/parsing/outil_lexer.c			\
			./srcs/parsing/quoting.c 			\
			./srcs/parsing/lexer.c 				\
			./srcs/parsing/get_command_line.c \
			./srcs/parsing/split_token.c 	\
			./srcs/parsing/outil.c			\
			./srcs/parsing/parser.c			\
			./srcs/parsing/outil_parser.c	\
			./srcs/alelaval/get_env.c		\
			./srcs/shell/create_shell.c		\
			./srcs/shell/create_envp.c		\
			./srcs/shell/env_add.c			\
			./srcs/shell/del_env.c			\
			./srcs/expansion/expansion.c		\
			./srcs/expansion/variables.c		\
			./srcs/expansion/outil_expension.c		\
			./srcs/expansion/outil_variables.c		\
			./srcs/expansion/outil_variables_2.c		\
			./srcs/expansion/split_string.c		\
			./srcs/expansion/outil_split.c		\
			./srcs/expansion/remove_quote.c		\
			./srcs/expansion/outil_remove_quote.c		\
			./srcs/expansion/path_generator.c		\
			./srcs/expansion/outil_path.c		\
			./srcs/builtin/echo.c			\
			./srcs/builtin/cd.c				\
			./srcs/builtin/env.c			\
			./srcs/builtin/pwd.c			\
			./srcs/builtin/export.c			\
			./srcs/builtin/unset.c			\
			./test_exec.c						\
			./srcs/exec/exec.c				\
			./srcs/execution/exec.c \
		./srcs/heredoc/heredoc.c \
		./srcs/redirections/append.c \
		./srcs/redirections/infile.c \
			#./srcs/exec/exec_pipe.c			\


OBJS	=	$(SRCS:.c=.o)

HEADER	=	./inc/

LIBFT	=	./libft/

LIBFT_A	=	./libft/libft.a

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address -fsanitize=leak

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
			@make -C $(LIBFT)
			ar rcs $(LIBFT_A) $(OBJS)
			ranlib $(LIBFT_A)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline

all:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		$(RM) $(OBJS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
