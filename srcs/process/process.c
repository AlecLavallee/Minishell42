/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/25 18:07:52 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	executor(t_pipex *pipex)
{
	// setup redirection when infile done
	int i = 0;
	int status;
	int ret;
	int fdin;
	int fdout;

	fdin = dup(0);
	fdout = dup(1);
	while (i < pipex->nb_cmds)
	{
		// redirect input
		dup2(fdin, 0);
		close(fdin);
		
		if (i == pipex->nb_cmds - 1)
		{
			// setting up output to do when outfile done
			// default output used (unmodified stdout)
			// fdout = dup(tmpout);
		}
		else
		{
			//create pipe for next command instead
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[2];
		}
		
		// redirect output
		dup2(fdout, 1);
		close(fdout);

		// creating child process
		ft_putstr("Before Command!\n");
		ret = fork();
		
		// 0 : child, -1 : error during fork
		if (ret == 0)
		{
			execve(pipex->cmds[i]->args[0], pipex->cmds[i]->args, pipex->envp);
			perror("execve");
			exit(EXIT_SUCCESS);
		}
		else
		{
			// On fork() error exit
			if (ret == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
			{
				ft_putstr("Success\n");
				exit (EXIT_SUCCESS);
			}
		}
		i++;
	}

	// restoring default input/output
	dup2(fdin, 0);
	dup2(fdout, 1);

	//closing standard input and output
	close(fdin);
	close(fdout);

	if (ret != 0)
		waitpid(ret, &status, WEXITED);
}
