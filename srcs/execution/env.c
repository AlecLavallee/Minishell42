/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:01:55 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/30 14:18:04 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		error(shell);
	paths = ft_split(path, ':');
	shell->paths = paths;
	if (paths)
		return (paths);
	return (NULL);
}
