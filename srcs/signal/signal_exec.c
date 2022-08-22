/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:51:53 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 10:51:55 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int exit_status;

void    signal_exec_handle(int signal)
{
    //extern int exit_status;
    exit_status += signal;

    if (signal == 2)
    {
        exit_status = 128 + SIGINT; //valeur de retour avec Ctrl + C ( 128 + 2 = 130)
        //global_shell->interrupt = 1;
        ft_putstr_fd("\n", 2);
        rl_replace_line("", 0); // pas besoin?
        rl_redisplay(); //pas besoin?
    }
}

void    signal_exec(void)
{
    signal(SIGINT, signal_exec_handle);
    signal(SIGQUIT, SIG_IGN); // qtrl + /
}