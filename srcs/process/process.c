/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/24 17:04:53 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	test_command(t_pipex *pipex, char *command)
{
	if (access(command, X_OK) != 0
		&& ft_strchr(command, '/') != NULL)
	{
		perror(command);
		pipex->ret = errno;
		error(pipex);
	}
}

/*void	first_command(t_pipex *pipex)
{
	if (pipex->file1 != -1)
		dup2(pipex->file1, STDIN_FILENO);
	else
	{
		ft_putstr(pipex->file1_name);
		ft_putstr(" : No such file or directory\n");
		close(pipex->end[0]);
		exit(-1);
	}
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->end[0]);
	test_command(pipex, pipex->command1);
	execve(pipex->command1, pipex->args1, pipex->envp);
	ft_putstr_fd(pipex->command1, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	pipex->ret = 127;
	error(pipex);
}

void	second_command(t_pipex *pipex)
{
	dup2(pipex->file2, STDOUT_FILENO);
	dup2(pipex->end[0], STDIN_FILENO);
	close(pipex->end[1]);
	test_command(pipex, pipex->command2);
	execve(pipex->command2, pipex->args2, pipex->envp);
	ft_putstr_fd(pipex->command2, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	pipex->ret = 127;
	error(pipex);
}*/

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
			ft_putstr("piping!\n");
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[2];
		}
		// redirect output
		dup2(fdout, 1);
		close(fdout);

		// creating child process
		ret = fork();
		if (ret == 0)
		{
			execve(pipex->cmds[i]->args[0], pipex->cmds[i]->args, pipex->envp);
			perror("execve");
			exit(1);
		}
		i++;
	}

	// restoring default input/output
	dup2(fdin, 0);
	dup2(fdout, 1);
	//closing standard input and output
	close(fdin);
	close(fdout);

	waitpid(ret, &status, 0);
	pipex->ret = WEXITSTATUS(status);
}
