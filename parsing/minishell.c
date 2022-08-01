/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:48:33 by msuji             #+#    #+#             */
/*   Updated: 2022/07/30 11:48:34 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int valeur_exit;
/*
    valeur_exit : variable global pour la valeur de retour, mais on pourrait enlever
*/
/* memo;

pour complier :
gcc minishell.h parsing/lexer.c parsing/outil_lexer.c parsing/minishell.c parsing/outil_signal.c parsing/quoting.c parsing/error.c libft/libft.a -lreadline
*/


//int main(int argc, char **argv, char **envp)
int main(int argc, char **argv)
{
    char *line;
    t_command *command_line;
    //int i;

    //i = 0;
    command_line = NULL;
    if (argc && argv)
    {
        while (1)
        {
            line = readline(">team_90's ");
            add_history(line);
            signal(SIGQUIT, SIG_IGN);
            if (signal(SIGINT, signal_input) == SIG_ERR)
                exit(1);
            if (line == NULL) 
            {
                free(line);
                break;
            }
            if (first_word_is_pipe(line) != 0)
                ft_error();
            if (!lexer(line, &command_line))
                printf("%s\n", line);
            free(line);
            free(command_line);
        }
    }
    printf("exit\n");
    free(line);
    return (valeur_exit);
}