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
# define PATH_MAX 4096

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
	//TOKEN_BUILTIN,
	TOKEN_PIPE, // | 
	TOKEN_OP, // operands
	TOKEN_EOF, // end of string
} t_token_kind;

typedef enum
{
    ARGUMENT, // word 0
    FILE_IN, // < 1
	FILE_OUT, // > 2
	OPEN_FILE, // < 3
	EXIT_FILE, // > 4
	FILE_OUT_SUR, // >> 5
 	HEREDOC, // << 6
	LIMITOR, //<< 7
	EXIT_FILE_RET, // >> 8
	BUILTIN, //builtin command = 9
	COMMAND,//10
	PIPE, // | 11
	OP, // operands 12
	NODE_EOF, // end of string 13
} t_node_kind;

typedef enum
{
	REDIR_OUT, // >
	REDIR_IN, // <
	REDIR_APPEND, // >>
	REDIR_HEREDOC, // <<
}	t_redir_kind;

typedef struct s_redir
{
	t_redir_kind kind;
	char *str;
	int fd;
	int cur;
	struct s_redir *next;
} t_redir;

typedef struct s_node {
  t_node_kind kind; // state_token
  struct s_node *next;
  int val;        // kindがTK_NUMの場合、その数値 = pas besoin pour minishell
  char *str;      // for word(=argument)
  int len;        // longuer_token
  struct s_node *lhs; //left handle
  struct s_node *rhs; // right handle
  struct s_cmd *cmds;
  t_redir *redir_in;
  t_redir *redir_out;
}t_node;

typedef struct s_word
{
	struct s_word *next;
	char *str;
} t_word;


typedef struct s_cmd
{
	t_redir *redir_in;
	t_redir *redir_out;
	t_word *word;
} t_cmd;



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

typedef struct s_env
{
	char *name;
	char *body;
	struct s_env *next;
} t_env;


/*
** alelaval's stducture
*/
typedef struct s_comm
{
	int		isbuiltin;
	int		pipe[2];
	char	**args;
	char	**files;
	struct s_comm	*next;
}			t_comm;

/*
**alelaval's structure
*/
typedef struct s_shell
{
	int			ret;
	int			definput;
	int			defoutput;
	int			fdin;
	int			fdout;
	char		*outfile;
	int			nb_cmds;
	t_comm		*cmds;
	char		**envp;
	char		**paths;
	t_env		*env; // ajoute
}				t_shell;

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
int	put_eof(t_command *command_line, char *str, int len);

//parser
t_node *stmt(t_token **token);
t_node *parser(t_token *token);
t_node *pipe_cmd(t_token **token);
t_node *command(t_token **token);
//void redir_in(t_token **token, t_node *node);
//void redir_out(t_token **token, t_node *node);
t_node *word(t_token **token);
void node_init(t_node *node); // provisoire

//expander
t_node expension(t_node *node);
char remove_quote(char *str);


//util_for_parser
int consume(t_token *token, t_token_kind kind, char *str);
t_token *skip(t_token *token, t_token_kind kind, char *str);
t_node *new_node_pipe(t_node *cmd_node);
t_node	*add_node_pipe(t_node *node, t_node *cmd_node);
t_node *new_node_command(void);
t_node *new_node_word(t_token *token);
void word_addback(t_cmd *command, char *str, long len);
void redir_in_addback(t_cmd *command, t_redir_kind kind, char *str, int len);
void redir_out_addback(t_cmd *command, t_redir_kind kind, char *str, int len);

//free
int    free_command_line(t_command *command_line);
void    free_token(t_command **command_line);
void free_node(t_node *node);
void free_word(t_word *word);
void free_redirection(t_redir *redir_in);

//env
t_shell *create_shell(char **envp, char **argv);
t_env	*create_env(char **envp);
t_env	*env_addback(t_env *env, char *name, char *body);
char	*create_env_name(char *str);
char	*create_env_body(char *str);
void    free_env(t_shell *shell);

//alelaval's focntion
t_shell	*init_all(void);
char	*get_path_line(char **paths);
char	**get_paths(t_shell *shell, char **envp);
void	exit_shell(t_shell *shell, int code);
void	free_all(t_shell *shell);
void	free_paths(t_shell *shell);
void	free_cmds(t_shell *shell);
void	fill_data(t_shell *shell, char **args);
void	lst_addback(t_comm **lst, t_comm *new);
int		isbuiltin(char *str);

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