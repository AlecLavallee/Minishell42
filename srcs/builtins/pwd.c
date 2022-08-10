/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:59:07 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/10 15:03:37 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	pwd()
{
	char buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	if (buff == NULL)
		perror("pwd");
	ft_putstr(buff);
}