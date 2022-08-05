/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:22:59 by msuji             #+#    #+#             */
/*   Updated: 2022/08/05 11:23:00 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int split_command_to_token(t_command **command_line)
{
    t_command *cur;

    cur = *command_line;
    while (cur)
    {
        if (split_command_line(&cur) > 0)
            return (1);
        cur = cur->next;
    }
    return (0);
}

int split_command_line(t_command **command_line)
{
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    len = ft_strlen((*command_line)->whole_str);
    while (cur < len)
    {
        while ((*command_line)->whole_str[cur] == ' ')
            cur++;
        start = cur;
        while (!is_redirection((*command_line)->whole_str[cur])
            && (*command_line)->whole_str[cur] != ' '
            && (*command_line)->whole_str[cur])
            cur++;
        tokenization(cur, start, (*command_line)->whole_str, command_line);
    }
    return (0);
}

int tokenization(int cur, int start, char *str, t_command **command_line)
{
    t_token *token;

    token = malloc(sizeof(t_token));
        if (token == NULL)
            return (1);
    init_token(token);
    token->string = malloc(sizeof(char *) * (cur - start + 1));
        if (token->string == NULL)
            return (1);
    //token->string = ft_substr(str, start, cur - start);
    token->string = ft_strncpy(token->string, str + start, cur - start);
    if (token->string == NULL)
        return (1);
    token_addback(&((*command_line)->first_token), token);
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