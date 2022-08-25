/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:33:04 by msuji             #+#    #+#             */
/*   Updated: 2022/08/01 10:33:06 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int exit_status;

/*
void ft_error(char *str)
{
    int i;
    int cur;

    i = 0;
    cur  = 0;
    while (str[i])
    {
        while (str[i] != '|' && str[i])
            i++;
        if (str[i] == '|')
        {
            if (str[i + 1] == '|')
                cur++;
            i++;
        }
    }
    if (cur == 0)
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    else
        ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);

}
*/