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

int get_command_line(char *str, t_command **command_line)
{
    t_command *new;    

    new = malloc(sizeof(t_command));
    if (new == NULL)
        return (1);

    init_command_line(new);
    new->whole_str = (char *)malloc(sizeof(char) * (ft_strlen(str)) + 1);
    if (new->whole_str == NULL)
        return (1);
    new->whole_str = ft_strcpy(new->whole_str, str);
    commandline_addback(command_line, new);
    //if (new == NULL)
    //    return (1);
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
        while (a->next)
		    a = a->next;
		a->next = new;
	}
}

void init_command_line(t_command *command_line)
{  
        command_line->command = NULL;
        command_line->cur = 0;
        command_line->whole_str = NULL;
        command_line->first_token = NULL;
}
