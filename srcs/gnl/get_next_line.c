/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:43:19 by alelaval          #+#    #+#             */
/*   Updated: 2021/07/16 18:43:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_secure(char **stock, char **line, int i)
{
	if (i == 1)
	{
		if (!stock || !line)
		{
			if (*stock)
			{
				free(*stock);
				*stock = NULL;
			}
			if (*line)
			{
				free(*line);
				*line = NULL;
			}
		}
		return (1);
	}
	if (*stock && i == 2)
	{
		free(*stock);
		*stock = NULL;
	}
	return (0);
}

int	stock_check(char ***line, char **stock)
{
	if (!stock[0])
	{
		stock[0] = malloc(sizeof(char));
		if (!*line[0] || !stock[0])
			return (-1);
		*stock[0] = '\0';
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int				i;
	static char		*stock = NULL;
	char			tmp[BUFFER_SIZE + 1];

	if (stock_check(&line, &stock))
		return (-1);
	i = read(fd, tmp, BUFFER_SIZE);
	while (i > 0)
	{
		tmp[i] = '\0';
		stock = ft_strcat(stock, tmp);
		if (ft_strclen(stock, '\n' == -1))
			i = read(fd, tmp, BUFFER_SIZE);
	}
	if (ft_strclen(stock, '\n') != -1)
	{
		*line = ft_strncpy(*line, stock, ft_strclen(stock, '\n'));
		stock = ft_strtrim_left(stock, ft_strclen(stock, '\n') + 1);
		return (ft_secure(&stock, line, 1));
	}
	*line = ft_strncpy(*line, stock, ft_strclen(stock, '\0'));
	return (ft_secure(&stock, line, 2));
}
