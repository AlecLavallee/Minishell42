/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:19:08 by msuji             #+#    #+#             */
/*   Updated: 2022/08/23 11:19:10 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    display_env_for_export(t_shell *shell)
{
    t_env *env;
    env = shell->env;
    while (env)
    {
        if (env->body)
            ft_printf("export %s=%s\n", env->name, env->body);
        else 
            ft_printf("export %s\n", env->name);
        env = env->next;
    }
}

int    export(t_word *word, t_shell *shell)
{
    if (word->next == NULL)
        display_env_for_export(shell);
    return (0);
}

/*
 gestion pour trois cas:
 1: export ENV sans '=' (faut pas afficher dans env)
 2: export ENV=...  (afficher dans env)
 3: export sans argument
*/