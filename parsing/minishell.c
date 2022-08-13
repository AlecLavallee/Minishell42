/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
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
    //t_node *node;


    //command_line = NULL;
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
            command_line = lexer(line);
                printf("%s\n", line);
            free(line);
        }
    }
    printf("exit\n");
    free_end(command_line, line);
    return (valeur_exit);
}

void	free_end(t_command *command_line, char *str)
{
	if (str)
		free(str);
	free_command_line(command_line);
}