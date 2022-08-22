/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:27:07 by mtsuji            #+#    #+#             */
/*   Updated: 2021/12/04 11:11:13 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	conversion_checker(char *format, t_count *count)
{
	if (format[count->index] == 'c')
		count->byte += ft_putchar_int(va_arg(count->argument, int));
	else if (format[count->index] == 's')
		count->byte += ft_putstr_for_printf(va_arg(count->argument, char *));
	else if (format[count->index] == 'p')
		count->byte += print_pointer(va_arg(count->argument, void *),
				format[count->index]);
	else if (format[count->index] == 'd' || format[count->index] == 'i')
		count->byte += ft_putnbr_for_printf(va_arg(count->argument, int));
	else if (format[count->index] == 'u')
		count->byte += ft_putnbr_for_printf(va_arg(count->argument, unsigned int));
	else if (format[count->index] == 'x' || format[count->index] == 'X')
		count->byte += to_hexadecimal(va_arg(count->argument, unsigned int),
				format[count->index]);
	else if (format[count->index] == '%')
		count->byte += ft_putchar_int('%');
}