/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:36:11 by alelaval          #+#    #+#             */
/*   Updated: 2021/12/18 17:50:34 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*ref;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	ref = str;
	if (start > ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	while (*(s + start) && len--)
	{
		*str++ = *(s + start);
		start++;
	}
	*str = '\0';
	return (ref);
}

static int	number(const char *s, char c)
{
	int	i;
	int	sub;

	i = 0;
	sub = 0;
	while (*s)
	{
		if (sub == 1 && *s == c)
			sub = 0;
		if (sub == 0 && *s != c)
		{
			sub = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static int	size(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s != c && *s != '\0')
	{
		size++;
		s++;
	}
	return (size);
}

static char	**panic(char **tab, int index)
{
	while (index--)
		free(tab[index]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_word;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	nb_word = number((const char *)s, c);
	tab = (char **)malloc(sizeof(*tab) * (number((const char *)s, c) + 1));
	if (!tab)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s)
			s++;
		tab[index] = ft_substr((const char *)s, 0, size((const char *)s, c));
		if (!tab[index])
			return (panic(tab, index));
		s = s + size(s, c);
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
