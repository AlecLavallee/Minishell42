/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:03:57 by msuji             #+#    #+#             */
/*   Updated: 2022/08/05 14:04:03 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strncpy(char *dest, const char *src, size_t n)
{
	 size_t i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
       dest[i] = src[i];
       i++;
    }
    dest[i] = '\0';

    return (dest);
}