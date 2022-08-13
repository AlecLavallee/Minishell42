/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:22:59 by msuji             #+#    #+#             */
/*   Updated: 2022/08/05 11:23:00 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
** version 08/12
static void redirection_end(char *str, int *cur)
{
    char c;
    c = str[*cur];
    while (c == str[*cur] && str[*cur])
        (*cur)++;
}

int word_end(char *str, int *cur)
{
    static int quote;

    quote = 0;
    while (str[(*cur)])
    {
        quote = is_quote(str[*cur], quote);
        if (is_separator(str[*cur]) == 1 && quote == 0)
            break ;
        (*cur)++ ;
    }
    return (0);
 }


 void init_type(t_token *new)
 {
    int len;

    if (new->string)
        len = ft_strlen(new->string);
    if (len == 1)
    {
        if (new->string[0] == '>')
            new->kind = FILE_OUT;
        if (new->string[0] == '<')
            new->kind = FILE_IN;
    }
    if (len == 2)
    {
        if (new->string[0] == '>' && new->string[1] == '>')
            new->kind = FILE_OUT_SUR; // il faut modifier
        if (new->string[0] == '<' && new->string[1] == '<')
            new->kind = DOC; //il faut modifier
    }
    if (checker_builtin(new->string))
        new->kind = BUILTIN;
    if (len != 0 && new->kind == DEFAULT)
        new->kind = ARGUMENT;

 }  
*/
/*
 void init_type(t_token *new)
 {
    int len;

    if (new->string)
        len = ft_strlen(new->string);
    if (len == 1)
    {
        if (new->string[0] == '>' || new->string[0] == '<')
            new->kind = OP;
    }
    if (len == 2)
    {
        if (new->string[0] == '>' && new->string[1] == '>')
            new->kind = OP; // il faut modifier
        if (new->string[0] == '<' && new->string[1] == '<')
            new->kind = OP; //il faut modifier
    }
    if (checker_builtin(new->string))
        new->kind = BUILTIN;
    if (len != 0 && new->kind == DEFAULT)
        new->kind = ARGUMENT;

 } 

static int tokenization(int cur, int start, char *str, t_command **command_line)
{
    t_token *token;

    token = malloc(sizeof(t_token)); // il faut changer
        if (token == NULL)
            return (1);
    init_token(token);
    token->string = malloc(sizeof(char *) * (cur - start + 1));
        if (token->string == NULL)
            return (1);
    token->string = ft_strncpy(token->string, str + start, cur - start);
    //if (token->string == NULL)
    //    return (1);
    init_type(token);
    token_addback(&((*command_line)->first_token), token);
    return (0);
}

static int split_command_line(t_command **command_line)
{
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    if ((*command_line)->whole_str != NULL)
        len = ft_strlen((*command_line)->whole_str);
    while (cur < len)
    {
        while (cur < len && (*command_line)->whole_str[cur] == ' ')
            cur++;
        start = cur;
        if (is_redirection((*command_line)->whole_str[cur]) && (*command_line)->whole_str[cur])
            redirection_end((*command_line)->whole_str, &cur);
        else 
            word_end((*command_line)->whole_str, &cur);
        if (tokenization(cur, start, (*command_line)->whole_str, command_line) > 0)
            return (1);
    }
    return (0);
}
int split_command_to_token(t_command **command_line)
{
    t_command *cur;

    cur = *command_line;
    while (cur)
    {
        if (split_command_line(&cur) > 0)
            return (1);
        cur = cur->next;
    }
    return (0);
}


*/

static void redirection_end(char *str, int *cur)
{
    char c;
    c = str[*cur];
    while (c == str[*cur] && str[*cur])
        (*cur)++;
}

int word_end(char *str, int *cur)
{
    static int quote;

    quote = 0;
    while (str[(*cur)])
    {
        quote = is_quote(str[*cur], quote);
        if (is_separator(str[*cur]) == 1 && quote == 0)
            break ;
        (*cur)++ ;
    }
    return (0);
 }
/*
 void init_type(t_token *new)
 {
    int len;

    if (new->string)
        len = ft_strlen(new->string);
    if (len == 1)
    {
        if (new->string[0] == '>')
            new->kind = FILE_OUT;
        if (new->string[0] == '<')
            new->kind = FILE_IN;
    }
    if (len == 2)
    {
        if (new->string[0] == '>' && new->string[1] == '>')
            new->kind = FILE_OUT_SUR; // il faut modifier
        if (new->string[0] == '<' && new->string[1] == '<')
            new->kind = DOC; //il faut modifier
    }
    if (checker_builtin(new->string))
        new->kind = BUILTIN;
    if (len != 0 && new->kind == DEFAULT)
        new->kind = ARGUMENT;

 }  
*/

 void init_type(t_token *new)
 {
    int len;

    if (new->string)
        len = ft_strlen(new->string);
    if (len == 1)
    {
        if (new->string[0] == '>' || new->string[0] == '<')
            new->kind = OP;
        if (new->string[0] == '|')
            new->kind = PIPE;
    }
    if (len == 2)
    {
        if (new->string[0] == '>' && new->string[1] == '>')
            new->kind = OP; // il faut modifier
        if (new->string[0] == '<' && new->string[1] == '<')
            new->kind = OP; //il faut modifier
    }
    if (checker_builtin(new->string))
        new->kind = BUILTIN;
    if (len != 0 && new->kind == DEFAULT)
        new->kind = ARGUMENT;

 } 

static int tokenization(int cur, int start, char *str, t_command *command_line)
{
    t_token *token;

    token = malloc(sizeof(t_token)); // il faut changer
        if (token == NULL)
            return (1);
    init_token(token);
    token->string = malloc(sizeof(char *) * (cur - start + 1));
        if (token->string == NULL)
            return (1);
    token->string = ft_strncpy(token->string, str + start, cur - start);
    token->len = cur - start;
    //if (token->string == NULL)
    //    return (1);
    init_type(token);
    token_addback(&(command_line)->first_token, token);
    return (0);
}

int	put_eof(t_command *command_line)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
    {
        free(token);
		printf("malloc error\n");
        return (1);
    }
	token->kind = TOKEN_EOF;
	token->string = 0;
	token->len = 0;
    token_addback(&command_line->first_token, token);
    return (0);
}

int split_command_line(t_command *command_line)
{
    int cur;
    int len;
    int start;

    cur = 0;
    len = 0;
    start = 0;
    if (command_line->whole_str != NULL)
        len = ft_strlen(command_line->whole_str + 1);
    while (cur < len)
    {
        while (cur < len && command_line->whole_str[cur] == ' ' )
            cur++;
        start = cur;
        if (is_redirection(command_line->whole_str[cur]) && command_line->whole_str[cur])
            redirection_end(command_line->whole_str, &cur);
        else 
            word_end(command_line->whole_str, &cur);
        if (tokenization(cur, start, command_line->whole_str, command_line) > 0)
            return (1);
    }
    if (put_eof(command_line) > 0)
        free(command_line);
    return (0);
}