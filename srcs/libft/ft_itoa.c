/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:15:19 by mtsuji            #+#    #+#             */
/*   Updated: 2021/06/07 16:51:01 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoalen(long nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dest;
	long	nb;
	int		i;

	i = 1;
	dest = malloc(sizeof(char) * (ft_itoalen(n) + 1));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
		dest[0] = '-';
	nb = n;
	if (nb < 0)
		nb = nb * -1;
	dest[ft_itoalen(n)] = '\0';
	while (nb >= 10)
	{
		dest[ft_itoalen(n) - i] = '0' + (nb % 10);
		nb = nb / 10;
		i++;
	}
	dest[ft_itoalen(n) - i] = '0' + (nb % 10);
	return (dest);
}
