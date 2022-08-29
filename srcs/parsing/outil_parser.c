/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:30:17 by msuji             #+#    #+#             */
/*   Updated: 2022/08/14 14:30:18 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//int exit_status;

void parser_error(char *str, long len)
{
    char *str_tmp;

    str_tmp = strndup(str, len);
    ft_putstr_fd("minishell : syntax error near unexpected token `newline'", 2);
//    ft_putstr_fd(str_tmp, 2);
    ft_putchar_fd('\n', 2);
    free(str_tmp);
    exit_status = 2;
    //exit(1);
}

bool consume(t_token *token, t_token_kind kind, char *str) 
{
	if (token->kind != kind)
		return (false);
	if (str != NULL && ft_strncmp(token->string, str, token->len))
		return (false);
	return (true);
}                         


t_token *skip(t_token *token, t_token_kind kind, char *str) 
{
	if (token->kind != kind)
    {
        //parser_error(token->string, token->len);
        exit_status = 5;
    }
	if (str != NULL && (token->len != (long)ft_strlen(str) 
        || ft_strncmp(token->string, str, token->len)))
    {
        exit_status = 5;
		//parser_error(token->string, token->len);
        //return (token);
    }
	return token->next;
}

/*
t_token *skip(t_token *token, t_token_kind kind, char *str) 
{
	if (token->kind != kind)
    {
        exit_status= 2;
        return (NULL);
    }
	if (str != NULL && (token->len != (long)ft_strlen(str) 
        || ft_strncmp(token->string, str, token->len)))
    {
		exit_status = 2;
        return (NULL);
    }
    else
	    return token->next;
}
*/
void free_node(t_node *node)
{
    if (node == NULL)
        return;
    if (node->kind != COMMAND)
    {
        free_node(node->lhs);
        free_node(node->rhs);
    }
    //free_node(node->next);
    //free_node(node->cmds);
    //free_node(node->redir_in);
    //free_node(node->redir_out);
    //free(node->str);
    else
    {
        free_word(node->cmds->word);
        free_redirection(node->cmds->redir_in);
        free_redirection(node->cmds->redir_out);
        free(node->cmds->pathname);
        free(node->cmds);
    }
    free(node);
}

void free_redirection(t_redir *redirection)
{
    if (!redirection)
        return ;
    free_redirection(redirection->next);
    free(redirection->str);
    //free_redir_in();
    free(redirection);
}

void free_word(t_word *word)
{
    if (!word)
        return ;
    free_word(word->next);
    free(word->str);
    free(word);
} 

t_node *new_node_pipe(t_node *cmd_node) 
{
    t_node *node;
    
    if (exit_status == 5)
        return (NULL);
    node = ft_calloc(1, sizeof(t_node));
    node->kind = PIPE;
    node->rhs = cmd_node; // right handle
    return (node);
}

t_node	*add_node_pipe(t_node *node, t_node *cmd_node)
{
	t_node	*new;

	new = new_node_pipe(cmd_node);
	new->lhs = node;
	return (new);
}

t_node *new_node_command(void)
{
    t_node *node;

    if (exit_status == 5)
        return (NULL);
    node = ft_calloc(1, sizeof(t_node));
    node->cmds = ft_calloc(1, sizeof(t_cmd));
    node->kind = COMMAND; 
    return (node);   
}

/*
t_node *new_node_word(t_token *token) 
{
    t_node *node;
    
    node = ft_calloc(1, sizeof(t_node));
    node->kind = ARGUMENT;
    node->str = malloc(sizeof(char *) * token->len + 1);
    node->str = ft_strncpy(node->str, token->string, token->len);
    return (node);
}
*/
void word_addback(t_cmd *command, char *str, long len) 
{
    t_word *word;
    t_word *last;
    
    word = ft_calloc(1, sizeof(t_word));
    word->str = ft_strndup(str, len);
    if (command->word == NULL) 
    {
        command->word = word;
        return ;
    }
    last = command->word;
    while (last->next != NULL) 
        last = last->next;
    last->next = word;
}

void redir_in_addback(t_cmd *command, t_redir_kind kind, char *str, int len) 
{
    t_redir *rdr;
    t_redir *last;

    rdr = ft_calloc(1, sizeof(t_redir));
    rdr->kind = kind;
    rdr->str = ft_strndup(str, len);
    if (command->redir_in == NULL)
    {
        command->redir_in = rdr;
        return ;
    }
    last = command->redir_in;
    while (last->next != NULL) 
        last = last->next;
    last->next = rdr;
}

void redir_out_addback(t_cmd *command, t_redir_kind kind, char *str, int len) 
{
    t_redir *rdr;
    t_redir *last;

    rdr = ft_calloc(1, sizeof(t_redir));
    rdr->kind = kind;
    rdr->str = ft_strndup(str, len);
    if (command->redir_out == NULL)
    {
        command->redir_out = rdr;
        return ;
    }
    last = command->redir_out;
    while (last->next != NULL) 
        last = last->next;
    last->next = rdr;
}

/* version 08/18
void redir_out_addback(t_node *command, t_node *rdr_out) 
{
    t_node *last;
    if (command->redir_out == NULL)
    {
        command->redir_out = rdr_out;
        return ;
    }
    last = command->redir_out;
    while (last->next != NULL) 
        last = last->next;
    last->next = rdr_out;
}
*/


void node_init(t_node *node)// provisoire
{
    node->lhs = NULL;
    node->rhs = NULL;
    node->next = NULL;
    node->cmds = NULL;
    node->redir_in = NULL;
    node->redir_out = NULL;   
}

void	_add_redir_in(t_node *node, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_strndup(str, len);
	redir->kind = kind;
	if (!node->redir_in)
		node->redir_in = redir;
	else
	{
		now = node->redir_in;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}