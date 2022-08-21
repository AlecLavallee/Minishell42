/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:54:18 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 23:54:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
version alelaval
void	pwd()
{
	char buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	if (buff == NULL)
		perror("pwd");
	ft_putstr(buff);
}
*/

int	pwd(t_word *word)
{
    (void)word;
	char buff[PATH_MAX];

    ft_memset(buff, 0, PATH_MAX); //initialization for variable
	if (!getcwd(buff, PATH_MAX))
		perror("pwd");
	ft_putendl_fd(buff, 1);
    return (0);
}


