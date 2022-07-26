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

/* memo;

pour complier :
gcc -Wall -Wextra -Werror  minishell.h lexer.c outil.c -lreadline libft/libft.a
*/
int valeur_exit;
/*
    valeur_exit : variable global pour la valeur de retour, mais on pourrait enlever
*/

int main(int argc, char **argv)
{
    char *line;

    line = NULL;
    if (argc && argv)
    {
        while (1)
        {
            if (signal(SIGINT, signal_input) == SIG_ERR)
                exit(1);
            line = readline(">team_90's ");
            if (line == NULL) 
            {
                free(line);
                break;
            }
            if (quote_check(line))
                printf("miss quote\n");
            else
                printf("%s\n", line);
            add_history(line);
            free(line);
        }
    }
    printf("exit\n");
    return (0);
}

int quote_check(char *str)
{
    int cur;

    cur  = 0;
    while (str[cur])
    {
        while (str[cur] == ' ')
            cur++;
        if (ft_strchr(str, '\''))
        {
            if (simple_quote(&str[cur]))
                return (STDERR);
            // fonction pour checker single quote
            else
                cur += simple_quote(&str[cur]);
        }
        else if (ft_strchr(str, '\"'))
        {
            // fonction pour checker double quote
            if (double_quote(&str[cur]))
                return (STDERR);
            else
                cur += double_quote(&str[cur]);
        }
        else 
            cur++;
    }
    return (0);
}

int simple_quote(char *str)
{
    int cur;
    int s_quote;

    cur = 0;
    s_quote = 0;
    while (str[cur])
    {
        if (str[cur] == '\'')
            s_quote++;
        cur++;
    }
    if (s_quote % 2 != 0)
        return (STDERR);
    return (0);
}

int double_quote(char *str)
{
    int cur;
    int d_quote;

    cur = 0;
    d_quote = 0;
    while (str[cur])
    {
        if (str[cur] == '\"')
            d_quote++;
        cur++;
    }
    if (d_quote % 2 != 0)
        return (STDERR);
    return (0);
}



