/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:17:06 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/25 18:00:08 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*a;

	while (*lst != NULL)
	{
		a = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = a;
	}
}
