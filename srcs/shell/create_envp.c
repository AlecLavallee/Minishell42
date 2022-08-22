/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:53:19 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 15:53:21 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long	get_env_size(t_shell *shell)
{
	long	size;
	t_env	*env;

	size = 0;
	env = shell->env;
	while (env)
	{
		if (env->body)
			size++;
		env = env->next;
	}
	return (size);
}

char	**create_envp(t_shell *shell)
{
	char		**envp;
	t_env		*env;
	long		i;
	const long	size = get_env_size(shell);

	envp = ft_calloc(size + 1, sizeof(char *));
	env = shell->env;
	i = 0;
	while (env)
	{
		if (env->body)
		{
			envp[i] = ft_strjoin(env->name, "=");
			envp[i] = ft_strjoin_and_free(envp[i], 1, env->body, 0);
			i++;
		}
		env = env->next;
}
	return (envp);
}

void	free_envp(char **envp)
{
	long	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i++]);
	}
	free(envp);
}