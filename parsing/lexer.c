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
    else
    {
        if (get_command_line(str, command_line) > 0)
            return (1);
        if (split_command_to_token(command_line) > 0)
            return (1);
        
    }
    //res = expension_word(command_line);
    return (0);
}

void    free_command_line(t_command **command_line)
{
    t_command *tmp;
    if (*command_line)
    {
        tmp = (*command_line)->next;
        if ((*command_line)->first_token)
            free((*command_line)->first_token);
        if ((*command_line)->whole_str)
            free((*command_line)->whole_str);
        if ((*command_line)->first_token)
            free_token(command_line);
        *command_line = tmp;
    }
}

void    free_token(t_command **command_line)
{
    int i;
    t_token *token;
    t_token *tmp;

    token = (*command_line)->first_token;
    while (token)
	{
        i = 0;
		tmp = token->next;
		if (token->string)
        {
            printf("[%d]:%s\n", i, token->string);
			free(token->string);
            token->string = NULL;
            i++;
        }
		free(token);
        token = tmp;
    }
}

