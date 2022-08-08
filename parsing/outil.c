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

int is_quote(char c, int quote)
{
    if (c == '\'' || c == '\"')
    {
        if (quote == 0)
            quote = 1;
        else if (quote == 1)
            quote = 0;
    }
    return (quote);
    /*if (quote == 0 && (c == '\'' || c == '\"'))
        return (1);
    if (quote == 1 && (c == '\'' || c == '\"'))
        return (0);
    else
        return (quote);*/
}

int is_separator(char c)
{
    if (c == ' ' || c == '<' || c == '>')
        return (1);
    return (0);
}

void    init_token(t_token *new)
{
    new->cur = 0;
    new->string = NULL;
    new->next = NULL;
}

void token_addback(t_token **tkn, t_token *new)
{
    t_token *a;

    a = *tkn;
	if (a == NULL)
		*tkn = new;
	else
	{
        while (a->next)
		    a = a->next;
		a->next = new;
	}
}

