/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:01:10 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/09 18:25:33 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		is_valid(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (0);
	}
	return (0);
}

void	echo(char **av)
{
	int	i;
	int j;
	int	option;

	i = 0;
	option = 0;
	j = 0;
	while (av[i])
	{
		while (av[i][j] == '-')
		{
			j++;
			while (av[i][j] == 'n')
				j++;
			if (av[i][j] == '\0')
				option = 1;
			else
				ft_putstr(av[i]);
			i++;
			j = 0;
		}
		while (av[i])
		{
			ft_putstr(av[i++]);
			ft_putchar(' ');
		}
	}
	if (option == 0)
		ft_putchar('\n');
}
