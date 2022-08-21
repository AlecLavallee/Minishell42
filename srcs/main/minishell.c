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

void start_command(char *str)
{
    t_command *command_line;
    t_node *node;

    command_line = lexer(str);
    node = parser(command_line->first_token);
    free_lexer(command_line);
    expand_var(node);
    free_node(node);
}



int main(int argc, char **argv, char **envp)
{
    char *line;
  
    if (argc && argv)
    {
        //shell = init_all();
        //shell->envp = get_paths(shell, envp);
        global_shell = create_shell(envp, argv);
        global_shell->exit_status = 0;
        signal_init();
        while (1)
        {
            signal_init();
            line = readline(">team_90's ");
            if (line == NULL) 
                break;

            if (only_space(line))
            {
                add_history(line);
                if (first_word_is_pipe(line) != 0)
                    ft_error();
                start_command(line);
            }
            printf("%s\n", line);
            free(line);
        }
    }
    ft_putstr_fd("exit\n", 2);
    exit_shell(global_shell, global_shell->exit_status); //  changed by mtsuji
}