/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:22:14 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/20 16:22:16 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../inc/minishell.h"

long	get_word_len_to_space(char *str)
{
	int	single_quote;
	int	double_quote;
	long	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (!double_quote && !single_quote && str[i] == ' ')
			break ;
		if (double_quote && str[i] == '"')
			double_quote = 0;
		if (single_quote && str[i] == '\'')
			single_quote = 0;
		if (!single_quote && !double_quote && str[i] == '\'')
			single_quote = 1;
		if (!single_quote && !double_quote && str[i] == '"')
			double_quote = 1;
		i++;
	}
	return (i);
}

t_word	*_create_splited_words(char *str)
{
	t_word	new_word;
	long	i;
	long	len;

	new_word.next = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		len = get_word_len_to_space(&(str[i]));
		word_add_back_for_split(&new_word, ft_strndup(&(str[i]), len));
		i += len;
	}
	return (new_word.next);
}

t_word	*_split_space_in_word(t_word *word)
{
	t_word	new_word;
	t_word	*last;

	if (word == NULL)
		return (NULL);
	/*if (word->dont_expand)
	{
		word->next = _split_space_in_word(word->next);
		return (word);
	}*/
	new_word.next = _create_splited_words(word->str);
	last = word_last(&new_word);
	last->next = _split_space_in_word(word->next);
	free(word->str);
	free(word);
	return (new_word.next);
}

void	split_space(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == NODE_EOF)
		return ;
	if (node->kind == COMMAND)
		node->cmds->word = _split_space_in_word(node->cmds->word);
	else
	{
		split_space(node->lhs);
		split_space(node->rhs);
	}
}