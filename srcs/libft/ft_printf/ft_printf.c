/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:42:22 by mtsuji            #+#    #+#             */
/*   Updated: 2021/12/04 11:16:06 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *format, ...)
{
	t_count	count;

	count.byte = 0;
	count.index = 0;
	va_start(count.argument, format);
	while (format[count.index])
	{
		print_before_sign((char *)format, &count);
		count.index++;
	}
	va_end(count.argument);
	return (count.byte);
}
