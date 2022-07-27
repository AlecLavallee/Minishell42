/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/27 18:13:30 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* handle_pipes
* setup pipes before forking and executing
* and redirects output to outfile if needed
// setting up output to do when outfile done
*/
void	handle_pipes(t_pipex *pipex, int i)
{
	if (i == pipex->nb_cmds - 1)
	{
		// default output used (unmodified stdout)
		// fdout = dup(tmpout);
	}
	else
	{
		int fdpipe[2];
		pipe(fdpipe);
		pipex->fdout = fdpipe[1];
		pipex->fdin = fdpipe[2];
	}
}

/* handle_input
* redirects standard input if needed
// setup redirection when infile done
*/
void	handle_input(t_pipex *pipex)
{
	dup2(pipex->fdin, 0);
	close(pipex->fdin);
}

/*	handle_output
* redirects standard output if needed
*/
void	handle_output(t_pipex *pipex)
{
	dup2(pipex->fdout, 1);
	close(pipex->fdout);
}

/*
* handle_io
* restoring default input/output
* closing standard input and output
*/
void	handle_io(t_pipex *pipex)
{
	dup2(pipex->fdin, 0);
	dup2(pipex->fdout, 1);
	close(pipex->fdin);
	close(pipex->fdout);
}

/*
* executor
* takes a list of commands
* establish pipes and redirections to share info
* and executing the commands provided
*/
void	executor(t_pipex *pipex)
{
	int		i;
	pid_t	ret;

	i = 0;
	pipex->fdin = dup(0);
	pipex->fdout = dup(1);
	while (i < pipex->nb_cmds)
	{
		handle_input(pipex);
		handle_pipes(pipex, i);
		handle_output(pipex);
		ret = fork();
		pipex->cmds[i]->pid = ret;
		if (ret == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (ret == 0)
		{
			if (!(access(pipex->cmds[i]->args[0], X_OK)))
				ft_putstr_fd("error command\n", 0);
			execve(pipex->cmds[i]->args[0], pipex->cmds[i]->args, pipex->envp);
			perror("execve");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	handle_io(pipex);
	int status = 0;
	waitpid(ret, &status, WEXITED);
}
