/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelaval <alelaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:33:19 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/25 18:36:32 by alelaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_redir_in(t_redir *redir_in)
{
	int	fd;

	if (redir_in == NULL)
		return (true);
	fd = -1;
	if (redir_in->kind == REDIR_IN)
	{
		fd = open(redir_in->str, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("redir_in->str", 2);
			ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	else if (redir_in->kind == REDIR_HEREDOC)
	{
		fd = create_heredoc(redir_in);
	}
	else
	{
		ft_putstr_fd("error: set_redir_in()", 2);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
	return (set_redir_in(redir_in->next));
}

bool	set_redir_out(t_redir *redir_out)
{
	int	fd;
	int	oflag;

	if (redir_out == NULL)
		return (true);
	oflag = 0;
	if (redir_out->kind == REDIR_OUT)
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir_out->kind == REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
	{
		ft_putstr_fd("error: set_redir_out()", 2);
		exit(1);
	}
	fd = open(redir_out->str, oflag, 0664);
	if (fd < 0)
	{
		printf("minishell: %s: \n", redir_out->str); //+error
		return (false);
	}
	dup2(fd, 1);
	close(fd);
	return (set_redir_out(redir_out->next));
}
