/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:49:18 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/20 19:49:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//int valeur_exit;

/*
** signal_input : gerer l'interruprion par clavier (Ctrl + c)
**
*/

//extern int exit_status;

void    signal_init_handle(int signal)
{
    //extern int exit_status;
    exit_status += signal;

    if (signal == 2)
    {
        exit_status = 128 + SIGINT; //valeur de retour avec Ctrl + C ( 128 + 2 = 130)
        ft_putstr_fd("\n", 2);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    if (signal == SIGQUIT) // ctrl + / = arreter execution = Quit (core dumped)
    {
        write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
        exit(1);
    }
}

void    signal_init(void)
{
    signal(SIGINT, signal_init_handle);
    signal(SIGQUIT, SIG_IGN); //
}