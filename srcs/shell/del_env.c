/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:47:18 by msuji             #+#    #+#             */
/*   Updated: 2022/08/24 10:47:25 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_for_unset(t_env *env)
{
    free(env->name);
    free(env->body);
    free(env);
}

void    del_env(char *name, t_shell *shell)
{
    t_env *env;
    t_env   *prev;

    env = shell->env;
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
        {
            if (env == shell->env)
                shell->env = env->next;
            else
                prev->next = env->next;
            free_for_unset(env);
            return ;
        }
        prev = env;
        env = env->next;
    }   
}

