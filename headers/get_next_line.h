/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:45:08 by alelaval          #+#    #+#             */
/*   Updated: 2020/09/29 05:10:48 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
int		ft_secure(char **stock, char **line, int i);
int		ft_strclen(const char *str, char c);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncpy(char *dst, char *src, int n);
char	*ft_strtrim_left(char *str, int n);

#endif
