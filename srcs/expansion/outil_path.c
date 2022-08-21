/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:23:59 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 13:24:01 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_path(char **paths)
{
	long	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/*
**fonction : acces <unistd.h>
**to confirm the pathneme(*char) has the corret right.
**option F_OK is to check the exintance of file
**if it's true = 0 / error = -1
*/
/*
**fonction : stat <sys/stat.h>
**to get the state of pathname(*char)= file/directory
**int stat(const char *path, struct stat *buf);
**buf is itructure of stat who contains the get state
**if it's true = 0 / error = -1
*/

int	check_pathname(char *pathname)
{
	struct stat	s;

	if (access(pathname, F_OK) != 0) 
		return (1);
	if (stat(pathname, &s) != 0)
		return (1);
	return (S_ISDIR(s.st_mode)); // normalement c'est 0 (success)
}
/*struct stat (menber)
**stat st_mode     genre of file and mode of acces protected
*/

/*
**macro
**S_ISREDIR(member) = check is directory or not 
*/

/*NB : Je voulais utiliser get_path de alelaval fonction,
**mais comme je n'avais pas besoin structure t_shell dedans
** je cree ma propre facon
*/
char	*sarch_pathname(char *str)
{
	char	**paths;
	char	*base;
	char	*pathname;
	long	i;

	pathname = NULL;
	paths = ft_split(get_env_body("PATH"), ':');
	if (paths == NULL)
		return (ft_strdup(str));
	i = 0;
	while (paths[i])
	{
		base = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin_and_free(base, 1, str, 0);
		if (!check_pathname(pathname))
		{
			free_path(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_path(paths);
	return (NULL);
}
