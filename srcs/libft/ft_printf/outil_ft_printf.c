/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:09:24 by mtsuji            #+#    #+#             */
/*   Updated: 2021/12/06 16:07:35 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar_int(char c)
{
	int	i;

	return (i = write(1, &c, 1));
}

int	ft_putstr_for_printf(char *str)
{
	int	i;

	if (!str)
		i = write(1, "(null)", 6);
	else
		i = write(1, &*str, ft_strlen(str));
	return (i);
}

int	ft_putnbr_for_printf(long nb)
{
	static int	byte;
	int			byte_minus;

	byte = 0;
	byte_minus = 0;
	if (nb < 0)
	{
		byte_minus = ft_putchar_int('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_for_printf(nb / 10);
		nb %= 10;
	}
	byte += ft_putchar_int(nb + 48);
	return (byte + byte_minus);
}
