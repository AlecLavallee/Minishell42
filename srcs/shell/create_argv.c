/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:19:07 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 18:19:10 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char **create_argv(t_word *word)
{
    char **argv;
    t_word *new;
    long len;
    int i;

    i = 0;
    new = word;
    while (new != NULL)
    {
        len++;
        new = new->next;
    }
    argv = ft_calloc(len + 1, sizeof(char *));
    while (word)
    {
        argv[i] = word->str;
        word = word->next;
        i++;
    }
    return (argv);
}