/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:15:39 by msuji             #+#    #+#             */
/*   Updated: 2022/07/30 12:15:51 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
**
** quote_check : checker des quotes impares dans le string
*/
int quote_check(char *str)
{
    int cur;
    int s_quote;
    int d_quote;

    cur  = 0;
    s_quote = 0;
    d_quote = 0;
    while (str[cur])
    {
        if (str[cur] == '\'')
            s_quote++;
        else if (str[cur] == '\"')
            d_quote++;
        cur++;
    }
    if (s_quote % 2 != 0 || d_quote % 2 != 0)
    {
        printf("miss_quote\n");
        return (STDERR);
    }
    return (0);
}