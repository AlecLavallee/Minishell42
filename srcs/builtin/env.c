/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:22:19 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 21:22:21 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int env(t_word *word, t_shell *shell)
{
    t_env *env;

    (void)word; // for unused paramator
    env = shell->env;
    while (env)
    {
        if (env->body)
            ft_printf("%s=%s\n", env->name, env->body);
        env = env->next;
    }
    return (0);
}