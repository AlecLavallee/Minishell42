/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:37 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/13 14:23:55 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* test for function and paths application */
char	*get_fun(char *arg, char **paths)
{
	int		i;
	char	*tmp;
	char	*join;

	// to do : check if features missing in bash documentation
	if (ft_strchr(arg, '/') != NULL)
		return (ft_strdup(arg));
	else
	{
		i = 0;
		join = ft_strjoin("/", arg);
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], join);
			if (access(tmp, X_OK) == 0)
			{
				free(join);
				return (tmp);
			}
			free(tmp);
			i++;
		}
		free(join);
	}
	return (ft_strdup(arg));
}

/* handle_input
* handle default streams and
* redirects standard input if needed
*/
void	handle_input(t_shell *shell, t_comm *cmd)
{
	shell->definput = dup(0);
	shell->defoutput = dup(1);
	// to consider : do I treat infile just like any file?
	if (cmd->infile)
		shell->fdin = open(cmd->infile, O_RDONLY);
	else
		shell->fdin = dup(shell->definput);
}

/* handle_pipes
* setup pipes before forking and executing
* and redirects output to outfile if needed
*/
void	handle_pipes(t_shell *shell, t_comm *cmd)
{
	int	fdpipe[2];

	dup2(shell->fdin, 0);
	close(shell->fdin);
	if (cmd->next == NULL)
	{
		// to do : gestion of multiple outfiles
		// in normal mode or in append
		if (cmd->outfile)
			shell->fdout = open(cmd->outfile, O_RDWR);
		else
			shell->fdout = dup(shell->defoutput);
	}
	else
	{
		pipe(fdpipe);
		shell->fdin = fdpipe[0];
		shell->fdout = fdpipe[1];
	}
	// to do : closing of multiples outfiles
	// or just closing the last one?
	dup2(shell->fdout, 1);
	close(shell->fdout);
}

/*
* handle_io
* restoring default input/output
* closing standard input and output
*/
void	handle_io(t_shell *shell)
{
	dup2(shell->definput, 0);
	dup2(shell->defoutput, 1);
	close(shell->definput);
	close(shell->defoutput);
}

void	exec_builtin(t_shell *shell)
{
	//to do : create an enum in the header with builtins listed
	ft_putstr("heheheha\n");
	if (!ft_strncmp(shell->cmds->args[0], "echo", ft_strlen(shell->cmds->args[0])))
		echo(&shell->cmds->args[1]);
	if (!ft_strncmp(shell->cmds->args[0], "pwd", ft_strlen(shell->cmds->args[0])))
		pwd();
}

/*
* executor
* takes a list of commands
* establish pipes and redirections to share info
* and executing the commands provided
*/
void	executor(t_shell *shell)
{
	int		status;
	t_comm	*cmd;
	pid_t	ret;

	cmd = shell->cmds;
	handle_input(shell, cmd);
	while (next)
	{
		handle_pipes(shell, cmd);
		if (!next->isbuiltin)
			ret = fork();
		else
			exec_builtin(shell);
		if (ret < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ret == 0)
		{
			cmd->args[0] = get_fun(cmd->args[0], shell->paths);
			execve(cmd->args[0], cmd->args, shell->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		cmd = cmd->next;
	}
	handle_io(shell);
	waitpid(ret, &status, WEXITED);
}
