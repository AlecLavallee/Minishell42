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
# include "../libft/libft.h"

typedef enum{
    DEFAULT, //default 0
    ARGUMENT, // word 1
    FILE_IN, // < 2 
	FILE_OUT, // > 3
	OPEN_FILE, // < 4
	EXIT_FILE, // > 5
	FILE_OUT_SUR, // >> 6
 	DOC, // << 7
	LIMITOR, //<< 8
	EXIT_FILE_RET, // >> 9
	BUILTIN, //builtin command = 10
} t_token_state;

typedef struct s_pars {
  t_token_state kind; // state_token
  struct s_pars *next;
  int val;        // kindがTK_NUMの場合、その数値 = pas besoin pour minishell
  char *str;      // string_token
  int len;        // longuer_token
}t_pars;

typedef struct s_token
{
	int				cur;
	int 			len;
    char            *string;
	char			*token;
	t_token_state	state;
	struct s_token	*next;
}		t_token;

typedef struct s_command
{
	int		cur;
	char	*whole_str;
	char	*command;
	t_token *first_token;
	struct s_command	*next;
}		t_command;

/*
typedef struct s_tc
{
	t_token **tkn;
	t_command *cmd;
	struct s_tc *next;
}	t_tc;
*/

extern int valeur_exit; 
void    signal_input(int signal);
int quote_check(char *str);
int simple_quote(char *str);
int double_quote(char *str);
int quoting(char *str);
//int lexer(char *str, t_command **command_line);
//int get_command_line(char *str, t_command **command_line);
//int split_command_to_token(t_command **command_line);
//int split_command_line(t_token **token, t_command **command);
//
int first_word_is_pipe(char *str);
//void init_command_line(t_command *command_line);
void	ft_error(void);


//lexer avec struct t_tc
int lexer(char *str, t_command **command_line);
int get_command_line(char *str, t_command **command_line);
//int filling_command_line(char *str, int cur, int start, t_command **command_line);
void check_pipe(int cur, char *str);
int split_command_to_token(t_command **command_line);
//int split_command_line(t_command **command_line);
//void init_command_line(t_command *command_line);
void token_addback(t_token **tkn, t_token *new);
t_token	*lstlast(t_token *lst);
//int tokenization(int cur, int start, char *str, t_command **command_line);
void    init_token(t_token *new);
void commandline_addback(t_command **line, t_command *new);
int is_redirection(char c);
int    free_command_line(t_command **command_line);
void    free_token(t_command **command_line);
int is_separator(char c);
int word_end(char *str, int *cur);
int is_quote(char c, int quote);
int checker_builtin(char *str);
//void is_pipe(int *cur, char *str);
//void redirection_end(char *str, int *cur);
int parser(t_token *tkn);
void	free_end(t_command **command_line, char *str);
# endif