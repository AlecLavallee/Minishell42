/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:45:47 by msuji             #+#    #+#             */
/*   Updated: 2022/07/25 14:45:49 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void    signal_quit_input(int signal)
{
    int sig_exit;

    sig_exit = 0;
    sig_exit += signal;
    if (sig_exit == 2)
    {
        printf("\n");
    }
    if (sig_exit == SIGQUIT)
    {
        printf("error----\n");
        exit(1);
    }
}

void    signal_input(int signal)
{
    int sig_exit;

    sig_exit = 0;
    sig_exit += signal;
    if (sig_exit == 2)
    {
        sig_exit = 130; //valeur de retour avec Ctrl + C
        printf("\n");
        printf(">team_90's ");
    }
}