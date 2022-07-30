/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 22:27:25 by mtsuji            #+#    #+#             */
/*   Updated: 2021/05/31 22:27:30 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;
	long	a;

	a = nb;
	if (a < 0)
	{
		write(fd, "-", 1);
		a = a * -1;
	}
	if (a >= 10)
	{
		ft_putnbr_fd((int)(a / 10), fd);
		ft_putnbr_fd((int)(a % 10), fd);
	}
	else
	{
		c = a + '0';
		write(fd, &c, 1);
	}
}
