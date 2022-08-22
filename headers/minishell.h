/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:53:20 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/22 13:59:07 by alelaval         ###   ########.fr       */
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

// Mtsuji
typedef enum{
    DEFAULT, //default 0
    TOKEN_ARGUMENT, // word 1
	TOKEN_PIPE, // | 
	TOKEN_OP, // operands
	TOKEN_EOF, // end of string
} t_token_kind;

typedef enum
{
	BUILTIN, 
	COMMAND,// word, redir
	PIPE, // | 
	NODE_EOF, // end of string 
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
	int		is_builtin;
	char	*pathname;
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

// alelaval
typedef struct s_comm
{
	int		isbuiltin;
	int		pipe[2];
	char	**args;
	char	**files;
	struct s_comm	*next;
}			t_comm;

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
}				t_shell;

// modified func
t_shell	*init_all(void);
void	exit_shell(t_shell *shell, int code);
char	*get_fun(char *arg, char **paths);
void	executor(t_shell *shell);
void	debug_data(t_shell *shell);
void	fill_data(t_shell *shell, char **args);
void	ft_shell(t_shell *shell);
// builtins
void	echo(char **av);
void	pwd();
// standard func
t_shell	*init_all(void);
t_shell	*parser(t_shell *shell, int count, char **args, char **paths);
void	first_command(t_shell *shell);
void	second_command(t_shell *shell);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		get_fd(t_shell *shell, char *arg, int com, char *path);
void	test_files(t_shell *shell, char **args);
int		size_array(char **array);
char	*get_path_line(char **paths);
char	**get_paths(t_shell *shell, char **envp);
void	free_all(t_shell *shell);
void	error(t_shell *shell);

#endif