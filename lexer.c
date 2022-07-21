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

/*
#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL "MINISHELL$ "
# define STDERR 2
# define STDIN 0
# define STDOUT 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
//# include "../lib/libft/libft.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int main(int argc, char **argv)
{
    char *line;

    line = NULL;
    if (argc && argv)
    {
        while (1)
        {
            line = readline(">minishell ");
            if (line == NULL || !ft_strlen(line))
            {
                free(line);
                break;
            }
            printf("%s\n", line);
            add_history(line);
            free(line);
        }
    }
    printf("exit\n");
    return (0);
}