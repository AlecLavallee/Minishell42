/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:28:01 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/17 13:28:04 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**alelaval's fonction
*/
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


/*
**alelaval's fonction
*/
char	**get_paths(t_shell *shell, char **envp)
{
	char	**paths;
	char	*path;

	path = get_path_line(envp);
	if (path == NULL)
		return(NULL);
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
	shell->nb_cmds = 0;
	shell->cmds = NULL;
	shell->envp = NULL;
	shell->paths = NULL;
	shell->ret = 1;
	//shell->env = NULL; //ajoute
	return (shell);
}

// ** alelaval' fontion but mtsuji changed 
void	exit_shell(t_shell *shell, int code)
{
	free_all(shell);
	exit(code);
}

void	free_cmds(t_shell *shell)
{
	int		i;
	t_comm	*tmp;

	while (shell->cmds)
	{
		i = -1;
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
		if (shell->env)//ajoute
			free_env(shell);//ajoute
		free(shell);
		shell = NULL;
	}
}

void	fill_data(t_shell *shell, char **args)
{
	int	i;
	t_comm *new;

	i = 0;
	while (args[i + 1])
	{
		new = (t_comm *)malloc(sizeof(t_comm));
		new->args = ft_split(args[i + 1], ' ');
		new->next = NULL;
		new->isbuiltin = isbuiltin(new->args[0]);
		lst_addback(&(shell->cmds), new);
		i++;
	}
	return;
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