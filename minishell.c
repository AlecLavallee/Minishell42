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

#include "./minishell.h"

int valeur_exit;
/*
    valeur_exit : variable global pour la valeur de retour, mais on pourrait enlever
*/
/* memo;

pour complier :
gcc -Wall -Wextra -Werror  minishell.h lexer.c outil.c minishell.c -lreadline libft/libft.a quoting.c 
*/


//int main(int argc, char **argv, char **envp)
int main(int argc, char **argv)
{
    char *line;
    t_command *command_line;
    //int i;
    //char **env_cpy;

    //i = 0;
    /*env_cpy = malloc(sizeof(char) * **envp + 1);
    while (*envp[i])
    {
        *env_cpy[i] = *envp[i];
        i++; 
    }*/
    /*
    ** il faut elaborer get_env
    */
   command_line = NULL;
    if (argc && argv)
    {
        while (1)
        {
            signal(SIGQUIT, SIG_IGN);
            if (signal(SIGINT, signal_input) == SIG_ERR)
                exit(1);
            line = readline(">team_90's ");
            if (line == NULL) 
            {
                free(line);
                break;
            }
            //if (!quote_check(line))
            if (!lexer(line, &command_line))
                printf("%s\n", line);
            add_history(line);
            free(line);
        }
    }
    printf("exit\n");
    free(line);
    //free(*env_cpy);
    return (valeur_exit);
}