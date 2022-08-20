/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_variables_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:30:29 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/20 15:30:31 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../inc/minishell.h"

 char	*ft_str_add_char(char *str, char c)
{
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	return (ft_strjoin_and_free(str, 1, ch, 0));
}

int	is_var_name_char_1st(char c)
{
	return (ft_isalpha(c) || c == '_'); // alphabet,_
}

int	is_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');// 英字,数字,_
}

char	*ft_strjoin_and_free(char *s1, int i1, char *s2, int i2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (i1)
		free(s1);
	if (i2)
		free(s2);
	return (str);
}