/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:45:52 by mtsuji            #+#    #+#             */
/*   Updated: 2021/05/31 22:20:34 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;

	src = (void *)s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
		{
			return (&src[i]);
		}
		i++;
	}
	return (NULL);
}
