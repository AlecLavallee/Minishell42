/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:24 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/27 18:18:15 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_pipex	*init_all(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc((sizeof(t_pipex)));
	if (!pipex)
		error(pipex);
	pipex->input = NULL;
	pipex->output = NULL;
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
	// allocating memories for chain of commands
	pipex->cmds = (t_comm**)malloc(sizeof(t_comm*) * 3 + 1);
	pipex->cmds[0] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[1] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[2] = (t_comm*)malloc(sizeof(t_comm) * 1);
	pipex->cmds[0]->args = (char **)malloc(sizeof(char *) * 3 + 1);
	pipex->cmds[1]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	pipex->cmds[2]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	pipex->cmds[3] = NULL;
	// Affecting commands and args
	pipex->cmds[0]->args[0] = "cat";
	pipex->cmds[0]->args[1] = "-e";
	pipex->cmds[0]->args[2] = "file1";
	pipex->cmds[0]->args[3] = NULL;
	pipex->cmds[1]->args[0] = "wc";
	pipex->cmds[1]->args[1] = "-l";
	pipex->cmds[1]->args[2] = NULL;
	pipex->cmds[2]->args[0] = "grep";
	pipex->cmds[2]->args[1] = "1";
	pipex->cmds[2]->args[2] = NULL;
}

void	debug_data(t_pipex *pipex)
{
	int i;
	int j;

	i = 0;
	while (pipex->cmds[i])
		i++;
	pipex->nb_cmds = i;
	printf("Number of commands : %d\n\n", pipex->nb_cmds);
	printf("infile:%s\n", pipex->input);
	printf("outfile:%s\n\n", pipex->output);
	i = 0;
	while (i < pipex->nb_cmds)
	{
		j = 0;
		while (pipex->cmds[i]->args[j])
		{
			printf("cmd[%d]->arg[%d]:%s\n", i, j, pipex->cmds[i]->args[j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
}

void	ft_pipex(t_pipex *pipex)
{
	int		status;
	pid_t	pid;

	pid = init_pid(pipex);
	executor(pipex);
	waitpid(pid, &status, 0);
	pipex->ret = WEXITSTATUS(status);
	ft_putstr_fd("Work is done\n", 0);
	exit (EXIT_SUCCESS);
}

int	main(int num_args, char **args, char **envp)
{

	t_pipex	*pipex;
	
	pipex = NULL;
	if (num_args)
	{
		(void)args;
		pipex = init_all();
		pipex->envp = get_paths(pipex, envp);
		if (!pipex->envp)
			printf("NULL ENVP!\n");
		// will be populated by Mariko's data later on
		//parser(pipex, num_args, args, paths);
		// write battery of tests
		fill_data(pipex);
		debug_data(pipex);
		printf("Running %d commands...\n", pipex->nb_cmds);
		ft_pipex(pipex);
		// no concerns for leaks right now
		// write garbage collector (later?)
		//free_all(pipex);
	}
	return (0);
}
