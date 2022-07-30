/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:24 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/30 14:32:27 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_shell	*init_all(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc((sizeof(t_shell)));
	if (!shell)
		error(shell);
	shell->input = NULL;
	shell->output = NULL;
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

void	fill_data(t_shell *shell)
{
	// allocating memories for chain of commands
	shell->cmds = (t_comm**)malloc(sizeof(t_comm*) * 3 + 1);
	shell->cmds[0] = (t_comm*)malloc(sizeof(t_comm) * 1);
	shell->cmds[1] = (t_comm*)malloc(sizeof(t_comm) * 1);
	shell->cmds[2] = (t_comm*)malloc(sizeof(t_comm) * 1);
	shell->cmds[0]->args = (char **)malloc(sizeof(char *) * 3 + 1);
	shell->cmds[1]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	shell->cmds[2]->args = (char **)malloc(sizeof(char *) * 2 + 1);
	shell->cmds[3] = NULL;
	// Affecting commands and args
	shell->cmds[0]->args[0] = "cat";
	shell->cmds[0]->args[1] = "-e";
	shell->cmds[0]->args[2] = "file1";
	shell->cmds[0]->args[3] = NULL;
	shell->cmds[1]->args[0] = "wc";
	shell->cmds[1]->args[1] = "-l";
	shell->cmds[1]->args[2] = NULL;
	shell->cmds[2]->args[0] = "grep";
	shell->cmds[2]->args[1] = "1";
	shell->cmds[2]->args[2] = NULL;
}

void	debug_data(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->cmds[i])
		i++;
	shell->nb_cmds = i;
	printf("Number of commands : %d\n\n", shell->nb_cmds);
	printf("infile:%s\n", shell->input);
	printf("outfile:%s\n\n", shell->output);
	i = 0;
	while (i < shell->nb_cmds)
	{
		j = 0;
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
	ft_putstr_fd("Work is done\n", 0);
	exit (EXIT_SUCCESS);
}

