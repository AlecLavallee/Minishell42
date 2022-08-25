/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:33:04 by msuji             #+#    #+#             */
/*   Updated: 2022/08/25 18:58:15 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int exit_status;

void ft_error(void)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    exit_status = 2;
}
