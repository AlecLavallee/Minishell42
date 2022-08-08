/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:44:08 by alelaval          #+#    #+#             */
/*   Updated: 2021/07/01 19:45:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strclen(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) \
		* (ft_strclen(s1, '\0') + ft_strclen(s2, '\0') + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strncpy(char *dst, char *src, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	(void)dst;
	if (n >= 0)
	{
		str = (char *)malloc(sizeof(char) * (ft_strclen(src, '\0') + n));
		if (str == NULL)
			return (NULL);
		while (src[i] && i < n)
		{
			str[i] = src[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

char	*ft_strtrim_left(char *str, int n)
{
	int	i;

	i = 0;
	while (str[n] != '\0')
	{
		str[i] = str[n];
		i++;
		n++;
	}
	str[i] = '\0';
	return (str);
}
