/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:24:18 by mtsuji            #+#    #+#             */
/*   Updated: 2021/06/07 14:45:03 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	a = 0;
	b = 0;
	while (dst[a])
		a++;
	while (src[b])
		b++;
	c = a;
	while (*src && a + 1 < dstsize)
		dst[a++] = *(src++);
	dst[a] = 0;
	if (c > dstsize)
		return (b + dstsize);
	return (b + c);
}
