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

#include "./minishell.h"

int lexer(char *str, t_command **command_line)
{
    int res;

    res = quote_check(str);
    if (res > 0)
        return (1);
    if (get_command_line(str, command_line) > 0)
        return (1);
    if (split_command_to_token(str, command_line) > 0)
        return (1);
    return (0);
}

int get_command_line(char *str, t_command **command_line)
{
    t_command *data;    
    int cur;

    cur = 0;
    data = malloc(sizeof(t_command));
    if (data == NULL)
        return (1);
    init_command_line(data);
    data->whole_str = strdup(str);
    return (0);
}

void init_command_line(t_command *command_line)
{  
    command_line->whole_str = NULL;
    command_line->argv = NULL;
    command_line->cur = 0;
}

int split_command_to_token(char *str, t_command **command_line)
{
    t_command *token;

    token = *command_line;
    while (token)
    {
        if (split_command_line(&token) > 0)
            return (1);
        token = token->next;
    } 
    return (0);

}

static int split_command_line(t_command **token)
{
    t_command *new;
    int cur;
    int len;

    cur = 0;
    len = 0;
    if ((*token)->whole_str != NULL)
        len = ft_strlen(new->whole_str + 1);
    while (cur < len)
    {
        if ((*token)->whole_str[cur] == ' ')
            cur++;
        if 
    }
    return (0);
}
