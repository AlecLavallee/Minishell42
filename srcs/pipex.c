/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:24 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/25 18:07:23 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_pipex	*init_all(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc((sizeof(t_pipex)));
	if (!pipex)
		error(pipex);
	pipex->envp = NULL;
	pipex->paths = NULL;
	pipex->ret = 1;
	return (pipex);
}

pid_t	init_pid(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork ");
		error(pipex);
	}
	return (pid);
}

void	fill_data(t_pipex *pipex)
{
	pipex->nb_cmds = 2;
	// allocating memories for chain of commands
	pipex->cmds = (t_comm**)malloc(sizeof(t_comm*) * 3 + 1);
	pipex->cmds[0] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[1] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[2] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[0]->args = (char **)malloc(sizeof(char *) * 3 + 1);
	pipex->cmds[1]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	pipex->cmds[2]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	// Affecting commands and args
	pipex->cmds[0]->args[0] = "cat";
	pipex->cmds[0]->args[1] = "-e";
	pipex->cmds[0]->args[2] = "file1";
	pipex->cmds[0]->args[3] = NULL;
	pipex->cmds[1]->args[0] = "wc";
	pipex->cmds[1]->args[1] = "-l";
	pipex->cmds[1]->args[2] = NULL;
	pipex->cmds[2]->args[0] = "wc";
	pipex->cmds[2]->args[1] = "-l";
	pipex->cmds[2]->args[2] = NULL;
	pipex->cmds[3] = NULL;
}

void	ft_pipex(t_pipex *pipex)
{
	int		status;
	pid_t	pid;

	pid = init_pid(pipex);
	executor(pipex);
	waitpid(pid, &status, 0);
	pipex->ret = WEXITSTATUS(status);
}

int	main(int num_args, char **args, char **envp)
{
	t_pipex	*pipex;
	char	**paths;

	paths = NULL;
	pipex = NULL;
	(void)num_args;
	(void)args;
	pipex = init_all();
	paths = get_paths(pipex, envp);
	pipex->envp = envp;
	(void)paths;
	// will be populated by Mariko's data later on
	//parser(pipex, num_args, args, paths);
	// write battery of tests
	fill_data(pipex);
	ft_pipex(pipex);
	// no concerns for leaks right now
	//free_all(pipex);
	return (0);
}
