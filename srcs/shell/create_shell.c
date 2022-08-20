/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:12:27 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/18 09:12:30 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


t_shell *create_shell(char **envp, char **argv)
{
    t_shell *shell;

    shell = NULL;
    shell = init_all();
    shell->envp = get_paths(shell, envp);
    if (!shell->envp)
        printf("NULL ENVP\n");
    fill_data(shell, argv);
    shell->env = create_env(envp);
    return (shell);
}

char	*create_env_name(char *str)
{
	char	*name;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq == NULL)
		name = ft_strdup(str);
	else
		name = ft_strndup(str, eq - str); 
	return (name);
}

char	*create_env_body(char *str)
{
	char	*body;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq == NULL)
		return (NULL);
	body = ft_strdup(eq + 1);
	return (body);
}

t_env	*env_addback(t_env *env, char *name, char *body)
{
	t_env	*now;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = name;
	new->body = body;
	if (env == NULL)
		return (new);
	else
	{
		now = env;
		while (now->next)
			now = now->next;
		now->next = new;
	}
	return (env);
}

t_env	*create_env(char **envp)
{
	t_env	*env;
	long	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = env_addback(env,
				create_env_name(envp[i]), create_env_body(envp[i]));
		i++;
	}
	return (env);
}

void    free_env(t_shell *shell)
{
    t_env *env;

    while (shell->env)
    {
        env = shell->env->next;
        free(shell->env->name);
        free(shell->env->body);
	    free(shell->env);
        shell->env = env;
    }
}