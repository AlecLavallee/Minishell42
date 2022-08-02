/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:24 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/02 18:33:40 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_shell	*init_all(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc((sizeof(t_shell)));
	if (!shell)
		error(shell);
	shell->infile = NULL;
	shell->outfile = NULL;
	shell->envp = NULL;
	shell->paths = NULL;
	shell->ret = 1;
	return (shell);
}

pid_t	init_pid(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork ");
		error(shell);
	}
	return (pid);
}

void	fill_data(t_shell *shell, int nb_args, char **args)
{
	int i;

	i = 0;
	// allocating memories for chain of commands
	shell->cmds = (t_comm**)malloc(sizeof(t_comm*) * nb_args + 1);
	// Affecting commands and args
	while (args[i + 1])
	{
		shell->cmds[i] = (t_comm*)malloc((sizeof(t_comm) * 1));
		shell->cmds[i]->args = ft_split(args[i + 1], ' ');
		i++;
	}
	shell->cmds[i] = NULL;
}

void	debug_data(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->cmds[i])
		i++;
	shell->nb_cmds = i;
	printf("Environment Paths:\n");
	i = 0;
	while (shell->paths[i])
	{
		printf("[%d]:[%s]\n", i, shell->paths[i]);
		i++;
	}
	printf("\n[Redirections]\n");
	printf("infile:%s\n", shell->infile);
	printf("outfile:%s\n\n", shell->outfile);
	i = 0;
	printf("[COMMANDS]\n\n");
	printf("Number of commands : %d\n\n", shell->nb_cmds);
	while (i < shell->nb_cmds)
	{
		j = 0;
		printf("[command %d]\n", i);
		while (shell->cmds[i]->args[j])
		{
			printf("cmd[%d]->arg[%d]:%s\n", i, j, shell->cmds[i]->args[j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
}

void	ft_shell(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = init_pid(shell);
	executor(shell);
	waitpid(pid, &status, 0);
	shell->ret = WEXITSTATUS(status);
	exit (EXIT_SUCCESS);
}
