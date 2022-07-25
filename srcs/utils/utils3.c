/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:38:17 by alelaval          #+#    #+#             */
/*   Updated: 2022/07/25 18:13:03 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((sizeof(char) * (len + 1)));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	return (str - len);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*tmp;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len++])
		;
	tmp = (char *)malloc(sizeof(char) * len);
	if (!tmp)
		return (NULL);
	while (len--)
		tmp[len] = s[len];
	return (tmp);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 && *str2 && (i < n - 1) && (*str1 == *str2))
	{
		str1++;
		str2++;
		i++;
	}
	return (*str1 - *str2);
}
