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

#include "../../inc/minishell.h"

int is_redirection(char c)
{
    if (c == '>' || c == '<')
        return (1);
    return (0);
}

int is_quote(char c, int quote)
{
    if (c == '\'')
    {
        if (quote == 0)
            quote = 2;
        else if (quote == 2)
            quote = 0;
    }
    if (c == '\"')
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
    new->len = 0;
    new->kind = DEFAULT;
    new->string = NULL;
    new->next = NULL;
}

/* version 08/12
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
*/
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


int checker_builtin(char *str)
{
    if (str == NULL)
        return (0);
    if (!ft_strcmp(str, "exit"))
        return (1);
    if (!ft_strcmp(str, "cd"))
        return (1);
    if (!ft_strcmp(str, "echo"))
        return (1);
    if (!ft_strcmp(str, "env"))
        return (1);
    if (!ft_strcmp(str, "export"))
        return (1);
    if (!ft_strcmp(str, "unset"))
        return (1);
    if (!ft_strcmp(str, "pwd"))
        return (1);
    else
        return (0); 
}
