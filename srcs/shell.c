/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:53:24 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/14 19:02:56 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	return (shell);
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
}

void	debug_data(t_shell *shell)
{
	int	i;
	int	j;
	t_comm *lst;

	i = 0;
	printf("Environment Paths:\n");
	while (shell->paths[i++])
		printf("[%d]:[%s]\n", i, shell->paths[i]);
	/*printf("\n[Redirections by default]\n");
	printf("[infile]:%s\n", shell->infile);
	printf("[outfile]:%s\n\n", shell->outfile);*/
	printf("[COMMANDS]\n\n");
	printf("Number of commands : %d\n\n", shell->nb_cmds);
	i = 0;
	lst = shell->cmds;
	while (lst->next)
	{
		lst = lst->next;
		shell->nb_cmds++;
	}
	shell->nb_cmds++;
	lst = shell->cmds;
	while (lst)
	{
		j = 0;
		printf("[command:%d]\n", i);
		printf("[IsBuiltin]:[%d]\n", lst->isbuiltin);
		while (lst->args[j])
		{
			printf("[cmd:%d][arg:%d]:%s\n", i, j, lst->args[j]);
			j++;
		}
		printf("\n");
		//printf("[infile]:%s\n[oufile]:%s\n\n", lst->infile, lst->outfile);
		lst = lst->next;
		i++;
	}
	printf("Running %d commands...\n", shell->nb_cmds);
}
