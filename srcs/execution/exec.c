/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/04 18:07:30 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* test for function and paths application */
char	*get_fun(char *arg, char **paths)
{
	int		i;
	char	*tmp;
	char	*join;

	if (ft_strchr(arg, '/') != NULL)
		return (ft_strdup(arg));
	else
	{
		i = 0;
		join = ft_strjoin("/", arg);
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], join);
			if (access(tmp, X_OK) == 0)
			{
				free(join);
				return (tmp);
			}
			free(tmp);
			i++;
		}
		free(join);
	}
	return (ft_strdup(arg));
}

/* handle_input
* handle default streams and
* redirects standard input if needed
*/
void	handle_input(t_shell *shell)
{
	shell->definput = dup(0);
	shell->defoutput = dup(1);
	if (shell->infile)
		shell->fdin = open(shell->infile, O_RDONLY);
	else
		shell->fdin = dup(shell->definput);
}

/* handle_pipes
* setup pipes before forking and executing
* and redirects output to outfile if needed
*/
void	handle_pipes(t_shell *shell, int i)
{
	int	fdpipe[2];

	dup2(shell->fdin, 0);
	close(shell->fdin);
	if (i == shell->nb_cmds - 1)
	{
		if (shell->cmds[i]->outfile)
			shell->fdout = open(shell->outfile, O_RDWR | O_APPEND);
		else
			shell->fdout = dup(shell->defoutput);
	}
	else
	{
		pipe(fdpipe);
		shell->fdin = fdpipe[0];
		shell->fdout = fdpipe[1];
	}
	dup2(shell->fdout, 1);
	close(shell->fdout);
}

/*
* handle_io
* restoring default input/output
* closing standard input and output
*/
void	handle_io(t_shell *shell)
{
	dup2(shell->definput, 0);
	dup2(shell->defoutput, 1);
	close(shell->definput);
	close(shell->defoutput);
}

/*
* executor
* takes a list of commands
* establish pipes and redirections to share info
* and executing the commands provided
*/
void	executor(t_shell *shell)
{
	int		i;
	int		status;
	pid_t	ret;

	i = 0;
	handle_input(shell);
	while (i < shell->nb_cmds)
	{
		handle_pipes(shell, i);
		ret = fork();
		if (ret < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ret == 0)
		{
			shell->cmds[i]->args[0] = get_fun(shell->cmds[i]->args[0], shell->paths);
			execve(shell->cmds[i]->args[0], shell->cmds[i]->args, shell->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	handle_io(shell);
	waitpid(ret, &status, WEXITED);
}
