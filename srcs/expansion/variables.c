/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:20 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/19 21:20:45 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../inc/minishell.h"

char	*expand_var_in_str(char *str)
{
	char	*new;
	long	i;
	int	double_quote;
	int	single_quote;

	new = ft_strdup("");
	double_quote = 0;
	single_quote = 0;
	i = 0;
	while (str[i])
	{
		if (!single_quote && str[i] == '$')
		{
			i = at_doller_mark(str, &new, i);
			continue ;
		}
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		new = ft_str_add_char(new, str[i]);
		i++;
	}
	free(str);
	return (new);
}

void	expand_var_in_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind != REDIR_HEREDOC)
		redir->str = expand_var_in_str(redir->str);
	expand_var_in_redir(redir->next);
}

void	expand_var_in_word(t_word *word)
{
	if (word == NULL)
		return ;
	word->str = expand_var_in_str(word->str);
	expand_var_in_word(word->next);
}

void	expand_var(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == NODE_EOF)
		return ;
	if (node->kind == COMMAND)
	{
		expand_var_in_word(node->cmds->word);
		expand_var_in_redir(node->cmds->redir_in);
		expand_var_in_redir(node->cmds->redir_out);
	}
	else
	{
		expand_var(node->lhs);
		expand_var(node->rhs);
	}
}
