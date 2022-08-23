/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:22:57 by mtsuji            #+#    #+#             */
/*   Updated: 2021/06/11 11:07:49 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*ret;

	if (lst == NULL)
		return (NULL);
	dest = ft_lstnew((f)(lst->content));
	if (dest == NULL)
		return (NULL);
	ret = dest;
	lst = lst->next;
	while (lst != NULL)
	{
		dest->next = ft_lstnew((f)(lst->content));
		if (dest->next == NULL)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		dest = dest->next;
		lst = lst->next;
	}
	dest->next = NULL;
	return (ret);
}
