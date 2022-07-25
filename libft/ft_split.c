/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 10:46:49 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/25 18:00:23 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	count_words(const char *str, char c)
{
	int	words;
	int	state;

	words = 0;
	state = 1;
	while (str && *str != '\0')
	{
		if (*str == c)
			state = 1;
		if (*str != c)
		{
			if (state == 1)
				words++;
			state = 0;
		}
		str++;
	}
	return (words);
}

static size_t	size_of_word(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	**free_split(char **dst, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(dst[j++]);
	free(dst);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = count_words((char *)s, c);
	dest = malloc(sizeof(char *) * (words + 1));
	if (dest == NULL)
		return (NULL);
	dest[words] = 0;
	i = -1;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{	
			dest[++i] = ft_substr(s, s - &s[0], size_of_word(s, c));
			if (dest[i] == NULL)
				return (free_split(dest, i));
			s = s + size_of_word((char *)s, c);
		}
	}
	return (dest);
}
