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

int check_argument_for_export(char *str)
{
    int i;

    i = 0;
    if (str[0] == '=' || (str[0] == '+' && str[1] == '='))
        return (1);
    while (str[i] && str[i] != '=' 
        && (str[i] != '+' || str[i + 1] != '='))
    {
        if (i == 0 && ft_isdigit(str[i]) == 1)
            return (1);
        if (ft_isalnum(str[i]) == 0 && str[i] != '_')
            return (1);
        i++;    
    }
    return (0);
}

int    export(t_word *word, t_shell *shell)
{
    int res;

    res = 0;
    if (word->next == NULL)
    {
        display_env_for_export(shell);
        return (0);
    }
    word = word->next;
    while (word)
    {
        res = check_argument_for_export(word->str);
        if (res != 0)
        {
            ft_printf("minishell : export: `%s' not a valid identifier\n", word->str); 
            return (1);
        }
        else
            env_add(word->str, shell);
        word =word->next;
    }
    return (0);
}

/*
 gestion pour trois cas:
 1: export ENV sans '=' (faut pas afficher dans env)
 2: export ENV=...  (afficher dans env)
 3: export sans argument
*/