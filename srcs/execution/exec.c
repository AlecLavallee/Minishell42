/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/25 18:58:00 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_node *node, t_shell *shell)
{
	t_cmd	*command;

	command = node->cmds;
	if (!ft_strncmp(command->word->str, "echo", ft_strlen(command->word->str)))
		exit_status = echo(command->word);
    else if (!ft_strncmp(command->word->str, "env", ft_strlen(command->word->str)))
		exit_status = env(command->word, shell);
	else if (!ft_strncmp(command->word->str, "pwd", ft_strlen(command->word->str)))
		exit_status = pwd(command->word);
	//if (!ft_strncmp(shell->cmds->args[0], "pwd", ft_strlen(shell->cmds->args[0])))
	//	pwd();
    else
    {
		ft_putstr_fd("no match command\n", 2);
		exit(1);
	}
}

/*
* exec_cmd
* execute a simple command
*/
void	exec_cmd(t_node *node, t_shell *shell)
{
	// need to test redirections further, might cause hanging
	if (!set_redir_in(node->cmds->redir_in)
		|| !set_redir_out(node->cmds->redir_out)
		|| node->cmds->word == NULL)
	{
		dup2(shell->fdin, 1);
		dup2(shell->fdout, 0);
		exit_status = 1;
		return ;
	}
	if (node->cmds->is_builtin)
		exec_builtin(node, shell);
	else
		exec_file(node, shell);
	dup2(shell->fdout, 1);
	dup2(shell->fdin, 0);
}

/*
* exec_recursion
* executes all piped commands using recursion
*/
void	exec_recursion(t_node *node, t_shell *shell)
{
	int	fd[2];
	int	pid;

	if (node == NULL)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (node->lhs)
			dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		exec_cmd(node->rhs, shell);
		exit(exit_status);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		exec_recursion(node->lhs, shell);
	}
	waitpid(pid, &(exit_status), 0);
	exit_status = WEXITSTATUS(exit_status);
}

/*
* executor
* takes the structure parsed with BNF
* establish pipes and redirections to share info
* and executing the commands provided
*/
void	executor(t_node *node, t_shell *shell)
{
	int		status;
	pid_t	pid;

	expander(node, shell);
	if (node->lhs == NULL)
		exec_cmd(node->rhs, shell);
	else
	{
		pid = fork();
		if (pid < 0)
			perror("fork");
		if (pid == 0)
		{
			exec_recursion(node, shell);
			exit(exit_status);
		}
	}
	status = 0;
	waitpid(pid, &status, 0);
	exit_status = WEXITSTATUS(status);
}
