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
/*
int lexer(char *str, t_command **command_line)
{
    int res;
    t_token *token;

    res = quote_check(str);    
    if (res > 0)
        return (1);
    if (get_command_line(str, command_line) > 0)
        return (1);
    if (split_command_to_token(command_line) > 0)
        return (1);
    while (token)
    {
        printf("%s\n", token->string);
        token = token->next;
    }
    return (0);
}
*/

/*
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
*/
/*
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
    //else
    //    (*command_line)->next = data;
    return (0);
}

void init_command_line(t_command *command_line)
{  
    command_line->whole_str = NULL;
    command_line->command = NULL;
    command_line->cur = 0;
}

int split_command_to_token(t_command **command_line)
{
    t_token *token;

    token = (t_token*)malloc(sizeof(t_token));
    if (token == NULL)
        return (1);
    //token = *command_line;
    if (split_command_line(&token, command_line) > 0)
        return (1);
    return (0);
}

int split_command_line(t_token **token, t_command **command)
{
    //t_command *new;
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    (*token)->string = NULL;
    if ((*command)->whole_str != NULL)
        len = ft_strlen((*command)->whole_str + 1);
    while (cur < len)
    {
        while ((*command)->whole_str[cur] == ' ')
            cur++;
        start = cur;
        while ((*command)->whole_str[cur] != ' ')
            cur++;
        (*token)->string = ft_substr((*command)->whole_str, start, cur - start);
        (*token)->string = (*token)->next->string;
    }
    return (0);
}
*/

int lexer(char *str)
{
    int res;
    t_tc **command_line;
    int i;

    i = 0;
    res = quote_check(str);    
    if (res > 0)
        return (1);
    t_tc *cmd_line = (t_tc*)malloc(sizeof(t_tc));
    command_line = &cmd_line;
    if (command_line == NULL)
        return (1);
    if (get_command_line(str, command_line) > 0)
        return (1);
    if (split_command_to_token(command_line) > 0)
        return (1);
    while ((*command_line)->tkn[i]->string)
    {
        printf("%s\n", (*command_line)->tkn[i]->string);
        i++;
    }
    return (0);
}

int get_command_line(char *str, t_tc **command_line)
{
    //t_command *data;    

    //data = (t_command*)malloc(sizeof(t_command));
    //if (data == NULL)
    //    return (1);

    (*command_line)->cmd = (t_command*)malloc(sizeof(t_command));
    (*command_line)->cmd->whole_str = (char *)malloc(sizeof(char) * (ft_strlen(str)) + 1);
     init_command_line(command_line);
    if ((*command_line)->cmd->whole_str == NULL)
        return (1);
    (*command_line)->cmd->whole_str = ft_strdup(str);
    if ((*command_line) == NULL)
        return (1);
    //else
    //    (*command_line)->next = data;
    return (0);
}

void init_command_line(t_tc **command_line)
{  
        (*command_line)->cmd->whole_str = NULL;
        (*command_line)->cmd->command = NULL;
        (*command_line)->cmd->cur = 0;
        //(*command_line)->tkn[0]->string = NULL;
}

int split_command_to_token(t_tc **command_line)
{
    //t_token *token;

    //token = (t_token*)malloc(sizeof(t_token));
    //if (token == NULL)
    //    return (1);
    //token = *command_line;
    if (split_command_line(command_line) > 0)
        return (1);
    return (0);
}

int split_command_line(t_tc **command_line)
{
    //t_command *new;
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    int i = 0;
    (*command_line)->tkn[i]->string = NULL;
    if ((*command_line)->cmd->whole_str != NULL)
        len = ft_strlen((*command_line)->cmd->whole_str + 1);
    while (cur < len)
    {
        while ((*command_line)->cmd->whole_str[cur] == ' ')
            cur++;
        start = cur;
        while ((*command_line)->cmd->whole_str[cur] != ' ')
            cur++;
        (*command_line)->tkn[i]->string = ft_substr((*command_line)->cmd->whole_str, start, cur - start);
        i++;
    }
    return (0);
}