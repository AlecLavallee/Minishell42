/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:02:19 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 18:02:52 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	exec_pipe(t_node *pipe_node)
{
	int	pid;
	int	sts;

	expander(pipe_node);
	if (pipe_node->lhs == NULL)
		exec_no_pipe(pipe_node);// go testfile
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_multi_pipes(pipe_node); // go testfile
			exit(global_shell->exit_status);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		global_shell->exit_status = WEXITSTATUS(sts);
	}
}