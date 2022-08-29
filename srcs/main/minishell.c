/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemina <jemina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:48:33 by msuji             #+#    #+#             */
/*   Updated: 2022/08/29 05:16:03 by jemina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exit_status;

void	start_command(char *str, t_shell *shell)
{
	t_command	*command_line;
	t_node		*node;

    //global_shell->interrupt = 0;
    command_line = lexer(str);
    node = parser(command_line->first_token);
    free_lexer(command_line);
    //expand_var(node);
    signal_exec();
    exec(node, shell);
    free_node(node);
}

int		main(int argc, char **argv, char **envp)
{

    char *line;
    t_shell *shell;

    if (argc && argv)
    {
        shell = create_shell(envp, argv);
        signal_init();
        while (1)
        {
            //exit_status = 0;
            signal_init();
            line = readline(">team_90's ");
            if (line == NULL) 
                break;
            if (only_space(line) && !first_word_colon_exclamation(line))
            {
                add_history(line);
                if (first_word_is_pipe(line) == 0)
                    start_command(line, shell);
            }
            printf("your command is : %s\n", line);
            free(line);
        }
    }
    ft_putstr_fd("exit\n", 2);
    exit_shell(shell, exit_status); //  changed by mtsuji
}