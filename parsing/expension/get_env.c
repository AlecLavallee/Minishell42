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
		return(NULL);
	paths = ft_split(path, ':');
	shell->paths = paths;
	if (paths)
		return (paths);
	return (NULL);
}