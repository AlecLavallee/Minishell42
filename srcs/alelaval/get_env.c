/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:28:01 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/25 18:58:09 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int exit_status;

char	*get_path_line(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (ft_strncmp("PATH=", paths[i], 5) == 0)
			return (paths[i] + 5);
		i++;
	}
	return (NULL);
}

char	**get_paths(t_shell *shell, char **envp)
{
	char	**paths;
	char	*path;

	path = get_path_line(envp);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	shell->paths = paths;
	if (paths)
		return (paths);
	return (NULL);
}

t_shell	*init_all(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc((sizeof(t_shell)) * 1);
	if (!shell)
		exit_shell(shell, EXIT_FAILURE);
	shell->envp = NULL;
	shell->paths = NULL;
	return (shell);
}

void	exit_shell(t_shell *shell, int code)
{
	free_all(shell);
	exit(code);
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
		if (shell->paths)
			free_paths(shell);
		if (shell->env)
			free_env(shell);
		free(shell);
		shell = NULL;
	}
}

int		isbuiltin(char *str)
{
	int			i;
	const char	*args[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;

	while (args[i])
	{
		if (ft_strncmp(str, args[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	lst_addback(t_comm **lst, t_comm *new)
{
	t_comm	*a;

	a = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (a->next)
			a = a->next;
		a->next = new;
	}
}
