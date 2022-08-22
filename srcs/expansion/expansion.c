/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:19:35 by msuji             #+#    #+#             */
/*   Updated: 2022/08/09 18:19:36 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void expander(t_node *node, t_shell *shell)
{
    expand_var(node, shell);
    split_space(node);
    remove_quote(node);
    pathname_generator(node, shell);
}