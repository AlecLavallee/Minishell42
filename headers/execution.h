/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:20 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/30 14:26:29 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct s_comm
{
	pid_t	pid;
	int		nb_args;
	char	**args;
}			t_comm;

typedef struct s_shell
{
	int			ret;
	int			fdin;
	int			fdout;
	char		*input;
	char		*output;
	const int	*end;
	int			nb_cmds;
	t_comm		**cmds;

	char		**envp;
	char		**paths;
}				t_shell;

// modified func
t_shell	*init_all(void);
void	executor(t_shell *shell);
void	debug_data(t_shell *shell);
void	fill_data(t_shell *shell);
void	ft_shell(t_shell *shell);
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