/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/30 14:18:04 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* handle_pipes
* setup pipes before forking and executing
* and redirects output to outfile if needed
// setting up output to do when outfile done
*/
void	handle_pipes(t_shell *shell, int i)
{
	int	fdpipe[2];

	if (i == shell->nb_cmds - 1)
	{
		// default output used (unmodified stdout)
		// fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		shell->fdout = fdpipe[1];
		shell->fdin = fdpipe[2];
	}
}

/* handle_input
* redirects standard input if needed
// setup redirection when infile done
*/
void	handle_input(t_shell *shell)
{
	shell->fdin = dup(0);
	dup2(shell->fdin, 0);
	close(shell->fdin);
}

/*	handle_output
* redirects standard output if needed
*/
void	handle_output(t_shell *shell)
{
	shell->fdout = dup(1);
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
	dup2(shell->fdin, 0);
	dup2(shell->fdout, 1);
	close(shell->fdin);
	close(shell->fdout);
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
	while (i < shell->nb_cmds)
	{
		handle_input(shell);
		handle_pipes(shell, i);
		handle_output(shell);
		ret = fork();
		shell->cmds[i]->pid = ret;
		if (ret == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (ret == 0)
		{
			if (!(access(shell->cmds[i]->args[0], X_OK)))
				ft_putstr_fd("error command\n", 0);
			execve(shell->cmds[i]->args[0], shell->cmds[i]->args, shell->envp);
			perror("execve");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	handle_io(shell);
	waitpid(ret, &status, WEXITED);
}
