/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:50:50 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/12 20:59:22 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_cmds(t_shell *shell)
{
	int		i;
	t_comm	*tmp;

	while (shell->cmds)
	{
		i = -1;
		if (shell->cmds->infile)
			free(shell->cmds->infile);
		if (shell->cmds->outfile)
			free(shell->cmds->outfile);
		shell->cmds->infile = NULL;
		shell->cmds->outfile = NULL;
		while (shell->cmds->args[++i])
		{
			free(shell->cmds->args[i]);
			shell->cmds->args[i] = NULL;
		}
		if (shell->cmds->args)
			free(shell->cmds->args);
		shell->cmds->args = NULL;
		tmp = shell->cmds;
		shell->cmds = shell->cmds->next;
		free(tmp);
	}
}

void	free_paths(t_shell *shell)
{
	int	i;

	if (shell->paths)
	{
		i = -1;
		while (shell->paths[++i])
		{
			free(shell->paths[i]);
			shell->paths[i] = NULL;
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
