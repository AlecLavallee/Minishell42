/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:50:50 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/05 18:06:08 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (shell->cmds[++i])
	{
		if (shell->cmds[i]->infile)
			free(shell->cmds[i]->infile);
		if (shell->cmds[i]->outfile)
			free(shell->cmds[i]->outfile);
		shell->cmds[i]->infile = NULL;
		shell->cmds[i]->outfile = NULL;
		j = 0;
		while (shell->cmds[i]->args[j])
		{
			free(shell->cmds[i]->args[j]);
			shell->cmds[i]->args[j] = NULL;
			j++;
		}
		free(shell->cmds[i]->args);
		shell->cmds[i]->args = NULL;
		free(shell->cmds[i]);
		shell->cmds[i] = NULL;
	}
	free(shell->cmds);
}

void	free_paths(t_shell *shell)
{
	int	i;

	if (shell->paths)
	{
		i = 0;
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			shell->paths[i] = NULL;
			i++;
		}
		free(shell->paths);
		shell->paths = NULL;
	}
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			free_cmds(shell);
		if (shell->paths)
			free_paths(shell);
		free(shell);
		shell = NULL;
	}
}

void	exit_shell(t_shell *shell, int code)
{
	free_all(shell);
	exit(code);
}
