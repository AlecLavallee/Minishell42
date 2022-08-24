/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:34:08 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/23 16:30:51 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fail_exec(t_node *node)
{
	exit_status = 126;
	if (errno == ENOENT)
		exit_status = 127;
	ft_putstr_fd("minishell: ", 1);
 	ft_putstr_fd(node->cmds->pathname, 1);
	ft_putstr_fd("\n", 1);
	return (exit_status);
}

void	set_exit_status(void)
{
	if (WIFSIGNALED(exit_status))
	{
		exit_status = 128 + WTERMSIG(exit_status);
		if (exit_status == 128 + SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
	else
		exit_status = WEXITSTATUS(exit_status);
}
