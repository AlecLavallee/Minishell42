/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:22:19 by msuji             #+#    #+#             */
/*   Updated: 2022/08/23 10:22:21 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_add(char *str, t_shell *shell)
{
    char *name;
    char *body;

    name = create_env_name(str);
    body = create_env_body(str);
    if (shell->env == NULL)
    {
        shell->env = new_env(name, body);
        return ;
    }
    env_rewrite(shell, name, body);
}

void	env_add_with_plus(char *str, t_shell *shell)
{
    char *name;
    char *body;

    name = create_env_name_with_plus(str);
    body = create_env_body_with_plus(str);
    if (shell->env == NULL)
    {
        shell->env = new_env(name, body);
        return ;
    }
    env_rewrite_with_plus(shell, name, body);
}

t_env   *new_env(char *name, char *body)
{
    t_env *env;

    env = ft_calloc(1, sizeof(t_env));
    env->name = name;
    env->body = body;
    return (env);
}

void env_rewrite(t_shell *shell, char *name, char *body)
{
    t_env *env;

    env = shell->env;
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
        {
            free(name);
            if (body)
            {
                free(env->body);
                env->body = body;
                //free(body);
            }
            return ;
        }
        if (env->next == NULL)
        {
            env->next = new_env(name, body);
            return ;
        }
        env = env->next;
    }   
}

void env_rewrite_with_plus(t_shell *shell, char *name, char *body)
{
    t_env *env;

    env = shell->env;
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
        {
            free(name);
            env->body = ft_strjoin_and_free(env->body, 1, body, 1);
            return ;
        }
        if (env->next == NULL)
        {
            env->next = new_env(name, body);
            return ;
        }
        env = env->next;
    }   
}