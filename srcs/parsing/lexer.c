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

#include "../../inc/minishell.h"
/*
version 08/12
int lexer(char *str, t_command *command_line)
{
    int res;
    //t_node *node;

    res = quote_check(str);
    if (res > 0)
        return (1);
    else
    {
        if (get_command_line(str, command_line))
        {
            free(str);
            free(command_line);
            return (1);
        }
        if (split_command_to_token(command_line) > 0)
        {
            free(str);
            free(command_line);
            return (1);
        }
    }
    //node = parser()//
    //res = expension_word(command_line);
    return (0);
}

int    free_command_line(t_command **command_line)
{
    t_command *tmp;
    
    if (*command_line)
    {
        while (*command_line)
        {
            tmp = (*command_line)->next;
            //if ((*command_line)->first_token)
            //    free((*command_line)->first_token);
            if ((*command_line)->whole_str)
                free((*command_line)->whole_str);
            if ((*command_line)->first_token)
                free_token(command_line);
            free(*command_line);
            *command_line = tmp;
        }
    }
    return (1);
}

void	free_token(t_command **command_line)
{
	t_token	*token;

    while ((*command_line)->first_token)
	{
	    token = (*command_line)->first_token->next;
	    if ((*command_line)->first_token->string)
		    free((*command_line)->first_token->string);
	    free((*command_line)->first_token);
	    (*command_line)->first_token = token;
	}
}
*/

t_command *lexer(char *str)
{
    int res;
    t_command *command_line;

    res = quote_check(str);
    if (res > 0)
        return (NULL);
    else
    {
        command_line = get_command_line(str);
        if (split_command_line(command_line) > 0)
        {
            free(str);
            free(command_line);
        }
    }
    //node = parser()//
    //res = expension_word(command_line);
    return (command_line);
}

int    free_lexer(t_command *command_line)
{
    
    if (command_line)
    {
        //while (command_line)
        //{
            if (command_line->whole_str)
                free(command_line->whole_str);
            if (command_line->first_token)
                free_token(&command_line);
            free(command_line);
        //}
    }
    return (1);
}

void	free_token(t_command **command_line)
{
	t_token	*token;

    while ((*command_line)->first_token)
	{
	    token = (*command_line)->first_token->next;
	    if ((*command_line)->first_token->string)
		    free((*command_line)->first_token->string);
	    free((*command_line)->first_token);
	    (*command_line)->first_token = token;
	}
}