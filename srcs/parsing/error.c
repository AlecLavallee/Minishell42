/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:33:04 by msuji             #+#    #+#             */
/*   Updated: 2022/08/01 10:33:06 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_error(void)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    global_shell->exit_status = 2;
}