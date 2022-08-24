/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:56:53 by msuji             #+#    #+#             */
/*   Updated: 2022/07/30 13:56:55 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
**is_redirection : on check s'il y a des orepand sur le string
**
*/
/*int is_redirection(t_command **command_line)
{
    
}*/
extern int exit_status;

int first_word_is_pipe(char *str)
{
    int cur;
    int p;

    cur  = 0;
    p = 0;
    while (str[cur])
    {
        if (str[cur] != ' ' && str[cur] != '|')
            p = 1;
        if (str[cur] == '|')
        {
            if (p == 0)
                return (1);
            p = 0;
        }
        cur++;
    }
    return (0);
}

int first_word_colon_exclamation(char *str)
{
    int cur;
    int p;

    cur  = 0;
    p = 0;
    while (str[cur])
    {
        if (str[cur] != ' ' && (str[cur] != ':' && str[cur] != '!'))
            p = 1;
        if (str[cur] == ':' || str[cur] == '!')
        {
            if (p == 0)
            {
                if (str[cur] == '!')
                    exit_status = 2;
                return (1);
            }
            p = 0;
        }
        cur++;
    }
    return (0);
}




