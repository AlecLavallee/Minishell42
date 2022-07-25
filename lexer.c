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
gcc -Wall -Wextra -Werror  minishell.h lexer.c outil_libft.c -lreadline

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
            printf("%s\n", line);
            add_history(line);
            free(line);
        }
    }
    printf("exit\n");
    return (0);
}

