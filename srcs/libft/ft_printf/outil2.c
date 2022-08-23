/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:09:17 by mtsuji            #+#    #+#             */
/*   Updated: 2021/12/06 16:07:18 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	to_hexadecimal(unsigned long long nb, char conversion)
{
	int	byte;

	byte = 0;
	if (nb <= 9)
		byte += ft_putchar_int(nb + '0');
	else if (nb >= 16)
	{
		byte += to_hexadecimal(nb / 16, conversion);
		byte += to_hexadecimal(nb % 16, conversion);
	}
	else
	{
		if (conversion == 'x')
			byte += ft_putchar_int(nb - 10 + 'a');
		else if (conversion == 'X')
			byte += ft_putchar_int(nb - 10 + 'A');
	}
	return (byte);
}

int	print_pointer(void *nb, char format)
{
	int				byte;
	void			*ptr;
	unsigned long	nbr;

	ptr = nb;
	nbr = (unsigned long) ptr;
	byte = 0;
	format = 'x';
	byte += ft_putstr_for_printf("0x");
	return (byte += to_hexadecimal(nbr, format));
}
