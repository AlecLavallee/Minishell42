/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:27:02 by msuji             #+#    #+#             */
/*   Updated: 2022/08/05 11:27:05 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_redirection(char c)
{
    if (c == '>' || c == '<')
        return (1);
    return (0);
}

int is_quote(char *str)
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
        //condition~~~
    }
    return (0);
}
