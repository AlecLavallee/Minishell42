/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:04:47 by mtsuji            #+#    #+#             */
/*   Updated: 2021/06/07 14:24:24 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	length;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	if (len > length)
	{
		len = length;
	}
	if (start >= length)
	{
		return (ft_strdup(""));
	}
	dst = malloc (sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		dst[i] = s[start + i];
	}
	dst[i] = '\0';
	return (dst);
}
