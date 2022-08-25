/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:29:27 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/25 18:37:53 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_heredoc(t_redir *redir)
{
	int		fd;
	char	*path;
	char	*line;

	// modif signals
	line = NULL;
	path = "tests/output";
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		perror("fd");
	else
	{
		// leaks
		// lines needs expanding (check GNU docs)
		line = readline("heredoc>");
		while (strcmp(line, redir->str) != 0)
		{
			ft_putstr_fd(line, fd);
			free(line);
			line = readline("heredoc>");
		}
		free(line);
		redir->str = ft_strdup(path);
	}
	return (fd);
}
