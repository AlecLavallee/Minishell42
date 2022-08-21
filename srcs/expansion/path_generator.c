/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:23:47 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 13:23:49 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
char	*get_pathname_str(char *str)
{
	char	*pathname;

	if (ft_strchr(str, '/'))
		pathname = ft_strdup(str);
	else
		pathname = sarch_pathname(str);
	return (pathname);
}

void pathname_generator(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == NODE_EOF)
		return ;
	if (node->kind == COMMAND)
	{
		if (node->cmds->word == NULL)
			return ;
		if (isbuiltin(node->cmds->word->str))
			node->cmds->is_builtin = 1;
		else
			node->cmds->pathname = get_pathname_str(node->cmds->word->str);
	}
	else
	{
		pathname_generator(node->lhs);
		pathname_generator(node->rhs);
	}
}   

