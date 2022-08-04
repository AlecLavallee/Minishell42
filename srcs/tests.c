/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:20:40 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/04 18:06:03 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int num_args, char **args, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	if (num_args > 1)
	{
		shell = init_all();
		shell->envp = get_paths(shell, envp);
		if (!shell->envp)
			printf("NULL ENVP!\n");
		// will be populated by Mariko's data later on
		//parser(shell, num_args, args, paths);
		// write battery of tests
		shell->infile = "tests/infile";
		shell->outfile = "tests/outfile";
		fill_data(shell, num_args, args);
		debug_data(shell);
		printf("Running %d commands...\n", shell->nb_cmds);
		executor(shell);
		// no concerns for leaks right now
		// write garbage collector (later?)
		free(shell);
	}
	return (0);
}
