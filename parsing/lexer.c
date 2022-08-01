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
    //if (split_command_to_token(str, command_line) > 0)
    //    return (1);
       printf("%s\n", (*command_line)->whole_str);
    return (0);
}

int get_command_line(char *str, t_command **command_line)
{
    t_command *data;    

    data = (t_command*)malloc(sizeof(t_command));
    if (data == NULL)
        return (1);
    init_command_line(data);
    data->whole_str = (char *)malloc(sizeof(char) * (ft_strlen(str)) + 1);
    if (data->whole_str == NULL)
        return (1);
    data->whole_str = ft_strdup(str);
    if ((*command_line) == NULL)
        (*command_line) = data;
    else
        (*command_line)->next = data;
    return (0);
}

void init_command_line(t_command *command_line)
{  
    command_line->whole_str = NULL;
    command_line->command = NULL;
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
    //t_command *new;
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    (*token)->command = NULL;
    if ((*token)->whole_str != NULL)
        len = ft_strlen((*token)->whole_str + 1);
    while (cur < len)
    {
        while ((*token)->whole_str[cur] == ' ')
            cur++;
        start = cur;
        while ((*token)->whole_str[cur] != ' ')
            cur++;
        (*token)->command = ft_substr((*token)->whole_str, start, cur - start);
        //token->command = token->next->command;
    }
    return (0);
}
