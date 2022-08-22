/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:01:10 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/22 13:56:09 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_rest(char **av, int i)
{
	while (av[i])
	{
		ft_putstr(av[i++]);
		ft_putchar(' ');
	}
}

/*
*	echo
*	outputs every arguments passed
*	if -n specified removes the trailing newline
*/
void	echo(char **av)
{
	int	i;
	int	j;
	int	option;

	i = 0;
	option = 0;
	j = 0;
	while (av[i][j] == '-' && av[i][j + 1] == 'n')
	{
		j++;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] == '\0')
			option = 1;
		else
			break ;
		i++;
		j = 0;
	}
	print_rest(av, i);
	if (option == 0)
		ft_putchar('\n');
}
