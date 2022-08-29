/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemina <jemina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:33:19 by alelaval          #+#    #+#             */
/*   Updated: 2022/08/29 06:06:14 by jemina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(t_redir *in)
{
	int		fd;
	char	*line;

	line = ft_strdup("");
	fd = open(in->str, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		return ;
	// strange issue, ft_strlen might be due to an error
	// when there's multiple heredoc with same name or direct sucession
	while (ft_strncmp(line, in->str, ft_strlen(in->str))
		|| ft_strlen(line) != ft_strlen(in->str))
	{
		line = readline("> ");
		if (ft_strlen(line) != ft_strlen(in->str))
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	close(fd);
	free(line);
}

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
			ft_putstr_fd("redir_in error", 2);
			ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	else if (redir_in->kind == REDIR_HEREDOC)
	{
		// will need expansion of every line expect delimiter
		// signal and exit_status too
		write_heredoc(redir_in);
		fd = open(redir_in->str, O_RDONLY, 0777);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("heredoc error", 2);
			ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	else
	{
		ft_putstr_fd("error: set_redir_in()", 2);
		// testing if kind not detected, removed exit
		return (false);
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
