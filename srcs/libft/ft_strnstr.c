/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:32:17 by mtsuji            #+#    #+#             */
/*   Updated: 2021/05/31 22:09:25 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	f;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		f = 0;
		while (haystack[i + f] == needle[f] && needle[f] != '\0' && f + i < len)
			f++;
		if (needle[f] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
