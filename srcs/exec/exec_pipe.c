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

extern int exit_status;

void	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pid;
	int	sts;

	expander(pipe_node, shell);
	if (pipe_node->lhs == NULL)
		exec_no_pipe(pipe_node, shell);// go testfile
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_multi_pipes(pipe_node, shell); // go testfile
			exit(exit_status);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		exit_status = WEXITSTATUS(sts);
	}
}