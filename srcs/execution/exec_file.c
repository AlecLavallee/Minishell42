/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:35:29 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/23 15:07:25 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_argv(t_word *word)
{
	char	**argv;
	long	len;
	t_word	*now;
	long	i;

	len = 0;
	now = word;
	while (now)
	{
		len++;
		now = now->next;
	}
	argv = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (word)
	{
		argv[i] = word->str;
		i++;
		word = word->next;
	}
	return (argv);
}

bool	is_directory(char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

int	check_cmd(t_cmd *cmd)
{
	if (cmd->pathname == NULL)
	{
		ft_putstr_fd("minishell:", 2);
        ft_putstr_fd(cmd->word->str, 2);
        ft_putstr_fd("command not found\n", 2);
		exit_status = 127;
		return (1);
	}
	if (is_directory(cmd->pathname))
	{
		printf("minishell: %s: is a directory\n", cmd->pathname); 
        ft_putstr_fd("minishell:", 2);
        ft_putstr_fd(cmd->pathname, 2);
        ft_putstr_fd("is a directory\n", 2);
		exit_status = 126;
		return (1);
	}
	return (0);
}

void	exec_file(t_node *node, t_shell *shell)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;
	int		exit_status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (check_cmd(node->cmds))
			exit(exit_status);
		cmd_argv = create_argv(node->cmds->word);
		cmd_envp = create_envp(shell);
		execve(node->cmds->pathname, cmd_argv, cmd_envp);
		free(cmd_argv);
		free_envp(cmd_envp);
		exit(fail_exec(node));
	}
	waitpid(pid, &(exit_status), 0);
	set_exit_status();
}
