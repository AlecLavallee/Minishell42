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

#include "../inc/minishell.h"

int consume(t_token *token, t_token_kind kind, char *str) 
{
	if (token->kind != kind)
		return (1);
	if (str != NULL && ft_strncmp(token->string, str, token->len))
		return (1);
	return (0);
}                         

t_token *skip(t_token *token, t_token_kind kind, char *str) 
{
	if (token->kind != kind)
    {
		printf("skip error : unexpected kind\n");
        exit(0); // modifier ares 
    }
	if (str != NULL && ft_strncmp(token->string, str, token->len))
    {
		printf("skip error : unexpectrd str\n");//error
        exit(0); //modifer apres
    }
	return token->next;
}

void free_node(t_node *node)
{
    if (node == NULL)
        return;
    free_node(node->lhs);
    free_node(node->rhs);
    free_node(node->next);
    free_node(node->cmds);
    free_node(node->redir_in);
    free_node(node->redir_out);
    free(node);
}

t_node *new_node_pipe(t_node *lhs, t_node *rhs) 
{
    t_node *node;
    
    node = ft_calloc(1, sizeof(t_node));
    node->kind = PIPE;
    node->lhs = lhs; // left handle 
    node->rhs = rhs; // right handle
    return (node);
}

t_node *new_node_command(void)
{
    t_node *node;

    node = ft_calloc(1, sizeof(t_node));
    node->kind = COMMAND; 
    return (node);   
}

t_node *new_node_word(t_token *token) 
{
    t_node *node;
    
    node = ft_calloc(1, sizeof(t_node));
    node->kind = ARGUMENT;
    node->str = ft_substr(token->string, 0, token->len);
    return (node);
}

void command_addback(t_node *command, t_node *word) 
{
    t_node *last;
    
    if (command->cmds == NULL) 
    {
        command->cmds = word;
        return ;
    }
    last = command->cmds;
    while (last->next != NULL) 
        last = last->next;
    last->next = word;
}

void redir_in_addback(t_node *command, t_node *rdr_in) 
{
    t_node *last;

    if (command->redir_in == NULL)
    {
        command->redir_in = rdr_in;
        return ;
    }
    last = command->redir_in;
    while (last->next != NULL) 
        last = last->next;
    last->next = rdr_in;
}

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

void node_init(t_node *node)// provisoire
{
    node->lhs = NULL;
    node->rhs = NULL;
    node->next = NULL;
    node->cmds = NULL;
    node->redir_in = NULL;
    node->redir_out = NULL;   
}