/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:32:32 by mtsuji            #+#    #+#             */
/*   Updated: 2021/06/08 15:42:52 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*s1;

	s1 = s;
	i = 0;
	while (i++ < (int)n)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
	}
	return (s1);
}
