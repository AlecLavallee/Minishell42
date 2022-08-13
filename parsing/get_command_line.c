/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:07:32 by msuji             #+#    #+#             */
/*   Updated: 2022/08/05 11:07:34 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
** version 08/12

static void is_pipe(int *cur, char *str)
{
    static int res;

    res = 0;
    while (str[*cur])
    {
        res = is_quote(str[*cur], res);
        if (res == 0 && str[*cur] == '|')
            return;
        (*cur)++;
    }
}

static void init_command_line(t_command *command_line)
{  
        command_line->command = NULL;
        command_line->cur = 0;
        command_line->whole_str = NULL;
        command_line->first_token = NULL;
        command_line->next= NULL;
}

static int filling_command_line(char *str, int cur, int start, t_command **command_line)
{
    t_command *new;    

    new = malloc(sizeof(t_command));
    if (new == NULL)
        return (1);
    init_command_line(new);
    new->whole_str = malloc(sizeof(char) * (cur - start + 1));
    if (new->whole_str == NULL)
    {
        free(new);
        return (1);
    }
    new->whole_str = ft_strncpy(new->whole_str, str + start, cur - start);
    commandline_addback(command_line, new);
    return (0);
}

int get_command_line(char *str, t_command **command_line)
{
    int cur;
    int start;

    cur = 0;
    start = 0;
    while (str[cur])
    {
        if (cur != 0)
        {
            cur++;
            start++;
        }
        is_pipe(&cur, str);
        if (filling_command_line(str, cur, start, command_line) > 0)
            return (1);
        start = cur;
        if (cur == 0)
        {
            cur++;
            start++;
        }
    }
    return (0);
}


void commandline_addback(t_command **line, t_command *new)
{
    t_command *a;

    a = *line;
	if (a == NULL)
		*line = new;
	else
	{
        while  (a->next)
		    a = a->next;
		a->next = new;
	}
}
*/

//version 08/13
/*static void is_pipe(int *cur, char *str)
{
    static int res;

    res = 0;
    while (str[*cur])
    {
        res = is_quote(str[*cur], res);
        if (res == 0 && str[*cur] == '|')
            return;
        (*cur)++;
    }
}*/

static void init_command_line(t_command *command_line)
{  
        command_line->command = NULL;
        //command_line->cur = 0;
        command_line->whole_str = NULL;
        command_line->first_token = NULL;
        //command_line->next= NULL;
}


t_command *get_command_line(char *str)
{   
    t_command *new;
    new = malloc(sizeof(t_command));
    if (new == NULL)
        exit (1);
    init_command_line(new);
    new->whole_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (new->whole_str == NULL)
    {
        free(new);
        exit (1);
    } 
    new->whole_str = ft_strcpy(new->whole_str, str);
    //commandline_addback(command_line, new);
    //command_line = new;
    return (new);
}

void commandline_addback(t_command *line, t_command *new)
{
    t_command *a;

    a = line;
	if (a == NULL)
		line = new;
	else
	{
        while  (a->next)
		    a = a->next;
		a->next = new;
	}
}