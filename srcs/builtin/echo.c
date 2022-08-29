/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:50:24 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 17:50:32 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int echo_option(char *str)
{
    long i;

    i = 1;
    if (ft_strncmp(str, "-n", 2) != 0)
    {
        return (1);
    }

    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

int	echo(t_word *word)
{
	int	option;
    t_word *arg;

    arg = word->next;
	option = 0;
    while (arg && !echo_option(arg->str))
	{
        option = 1;
        arg = arg->next;
    }
    while (arg)
    {
        ft_putstr_fd(arg->str, 1);
        arg = arg->next;
        if (arg)
            ft_putstr_fd(" ", 1);
    }
	if (option == 0)
		ft_putchar_fd('\n', 1);
    return (0);
}
