/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:23 by msuji             #+#    #+#             */
/*   Updated: 2022/07/21 17:10:27 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL "MINISHELL$ "
# define STDERR 2
# define STDIN 0
# define STDOUT 1
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_token
{
	int				cur;
	int 			len;
    char            *string;
	struct s_token	*next;
}		t_token;

typedef struct s_command
{
	char    **copy_env;
	int		cur;
	char	*str;
	char *argv;
	struct s_command	*next;
}		t_command;

extern int valeur_exit; 
void    signal_input(int signal);
int quote_check(char *str);
int simple_quote(char *str);
int double_quote(char *str);
int quoting(char *str);
int lexer(char *str, t_command **command_line);
int get_command_line(char *str, t_command **command_line);
int split_command_to_token(char *str, t_command **command_line);
int split_command_line(t_command **token);
void init_command_line(t_command *command_line);
# endif