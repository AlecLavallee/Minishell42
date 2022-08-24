/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:33:41 by msuji             #+#    #+#             */
/*   Updated: 2022/08/24 10:33:43 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset(t_word *word, t_shell *shell)
{

    word = word->next;
    while (word)
    {
        if (word->str)
            del_env(word->str, shell);
        word = word->next;
    }
    return (0);
}