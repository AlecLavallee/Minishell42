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

//int valeur_exit;

/*
** signal_input : gerer l'interruprion par clavier (Ctrl + c)
**
*/
void    signal_input(int signal)
{
    int valeur_exit;

    valeur_exit = 0;
    valeur_exit += signal;
    if (valeur_exit == 2)
    {
        valeur_exit = 130; //valeur de retour avec Ctrl + C
        printf("\n");
        printf(">team_90's ");
    }
}
