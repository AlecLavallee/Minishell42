/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:20:40 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/14 19:43:07 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int num_args, char **args, char **envp)
{
	int		debug;
	t_shell	*shell;

	shell = NULL;
	debug = 0;
	if (num_args > 1)
	{
		shell = init_all();
		shell->envp = get_paths(shell, envp);
		if (!shell->envp)
			printf("NULL ENVP!\n");
		// will be populated by Mariko's data later on
		//parser(shell, num_args, args, paths);
		fill_data(shell, args);
		if (debug)
			debug_data(shell);
		executor(shell);
		exit_shell(shell, EXIT_SUCCESS);
	}
	return (0);
}
