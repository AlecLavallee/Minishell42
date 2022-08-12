/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/12 14:54:02 by alelaval         ###   ########.fr       */
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
void	handle_pipes(t_shell *shell)
{
	int	fdpipe[2];

	dup2(shell->fdin, 0);
	close(shell->fdin);
	if (!(shell->cmds->next))
	{
		if (shell->cmds->outfile)
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

void	exec_builtin(t_shell *shell)
{
	ft_putstr("heheheha\n");
	if (!ft_strncmp(shell->cmds->args[0], "echo", ft_strlen(shell->cmds->args[0])))
		echo(&shell->cmds->args[1]);
	if (!ft_strncmp(shell->cmds->args[0], "pwd", ft_strlen(shell->cmds->args[0])))
		pwd();
}

/*
* executor
* takes a list of commands
* establish pipes and redirections to share info
* and executing the commands provided
*/
void	executor(t_shell *shell)
{
	int		status;
	pid_t	ret;

	handle_input(shell);
	while (shell->cmds)
	{
		handle_pipes(shell);
		if (!shell->cmds->isbuiltin)
			ret = fork();
		else
			exec_builtin(shell);
		if (ret < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ret == 0)
		{
			shell->cmds->args[0] = get_fun(shell->cmds->args[0], shell->paths);
			execve(shell->cmds->args[0], shell->cmds->args, shell->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		shell->cmds = shell->cmds->next;
	}
	handle_io(shell);
	waitpid(ret, &status, WEXITED);
}
