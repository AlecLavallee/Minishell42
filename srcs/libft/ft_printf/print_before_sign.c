/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_before_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:42 by mtsuji            #+#    #+#             */
/*   Updated: 2021/11/30 16:10:58 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_before_sign(char *format, t_count *count)
{
	if (format[count->index] != '%')
		count->byte += ft_putchar_int(format[count->index]);
	if (format[count->index] == '%')
	{
		count->index++;
		conversion_checker(format, count);
	}
}
