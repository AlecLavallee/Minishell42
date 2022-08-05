/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:29:54 by msuji             #+#    #+#             */
/*   Updated: 2022/07/21 14:29:59 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int lexer(char *str, t_command **command_line)
{
    int res;

    res = quote_check(str);    
    if (res > 0)
        return (1);
    if (get_command_line(str, command_line) > 0)
        return (1);
    if (split_command_to_token(command_line) > 0)
        return (1);
    return (0);
}

void    free_command_line(t_command **command_line)
{
    t_token *token;
    token = (*command_line)->first_token;
    free((*command_line)->whole_str);
    free((*command_line)->first_token);
    free(token->string);
    free(token);
}