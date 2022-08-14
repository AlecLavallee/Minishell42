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
    TOKEN_ARGUMENT, // word 1
	TOKEN_BUILTIN,
	TOKEN_PIPE, // | (mais je n'ai pas dintigue)
	TOKEN_OP, // operands
	TOKEN_EOF, // end of string
} t_token_kind;

typedef enum
{
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
	PIPE, // | (mais je n'ai pas dintigue)
	OP, // operands
	NODE_EOF, // end of string
} t_node_kind;


typedef struct s_node {
  t_node_kind kind; // state_token
  struct s_node *next;
  int val;        // kindがTK_NUMの場合、その数値 = pas besoin pour minishell
  char *str;      // for word(=argument)
  int len;        // longuer_token
  struct s_node *lhs; //left handle
  struct s_node *rhs; // right handle
  struct s_node *cmds;
  struct s_node *redir_in;
  struct s_node *redir_out;
}t_node;

typedef struct s_token
{
	int				cur;
	int 			len;
    char            *string;
	t_token_kind	kind;
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
int first_word_is_pipe(char *str);

void	ft_error(void);



//lexer
t_command *lexer(char *str);
int is_quote(char c, int quote);

//get_command_line
t_command *get_command_line(char *str);
int filling_command_line(char *str, int cur, int start, t_command **command_line);
void commandline_addback(t_command *line, t_command *new);
void check_pipe(int cur, char *str);

//tokenization
void	free_end(t_command *command_line, char *str);
int split_command_line(t_command *command_line);
int split_command_to_token(t_command *command_line);
void token_addback(t_token **tkn, t_token *new);
void    init_token(t_token *new);
int is_redirection(char c);
int is_separator(char c);
int word_end(char *str, int *cur);
int checker_builtin(char *str);

//parser
t_node *parser(t_token *token);
t_node *pipe_cmd(t_token **token);
t_node *command(t_token **token);
t_node *redir_in(t_token **token);
t_node *redir_out(t_token **token);
t_node *word(t_token **token);


//util_for_parser
int consume(t_token *token, t_token_kind kind, char *str);
t_token *skip(t_token *token, t_token_kind kind, char *str);
t_node *new_node_pipe(t_node *lhs, t_node *rhs);
t_node *new_node_command(void);
t_node *new_node_word(t_token *token);
void command_addback(t_node *command, t_node *word);
void redir_in_addback(t_node *command, t_node *rdr_in);
void redir_out_addback(t_node *command, t_node *rdr_out);

//free
int    free_command_line(t_command *command_line);
void    free_token(t_command **command_line);
void free_node(t_node *node);


// lexer version until 08/12 (double pointeur)
/*
int lexer(char *str, t_command **command_line);
int get_command_line(char *str, t_command **command_line);
int split_command_to_token(t_command **command_line);
void token_addback(t_token **tkn, t_token *new);
void commandline_addback(t_command **line, t_command *new);
int    free_command_line(t_command **command_line);
void	free_end(t_command **command_line, char *str);

** supprime
void is_pipe(int *cur, char *str);

*/



# endif