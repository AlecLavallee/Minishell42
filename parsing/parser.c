/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:36:50 by msuji             #+#    #+#             */
/*   Updated: 2022/08/12 16:16:36 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int parser(t_token *tkn)
{

    return (0);
}
*/
/*
construction de parsing:
en utilisant la regle EBNF(Extended BNF(Backs-Naur form)) par chque token,
apres on parse par chaque resultat de token.
ordre d'algo : 
1 word
2 redir in /out
3 command(builtin)
4 pipe command (separateur)
*/

/*
## EBNF pour  VRAI shell
parser    = stmt EOF
stmt      = pipe_cmd ("||" | "&&") pipe_cmd)*  ";"? separator
pipe_cmd  = bracket ("|" bracket)*
bracket   = "(" stmt ")"
          | cmd
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...

=============

## EBNF pour Minishell 
parser    = pipe_cmd EOF
pipe_cmd  = command ("|" command)*
command   = word (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
EOF       = ε (nothing (= 0))
*/


//ordre de fonction parser
t_node *parser(t_token *token); // -> pipe_cmd
t_node *pipe_cmd(t_token **token);// -> command
t_node *command(t_token **token);// -> word | redir_in | redir_out
t_node *redir_in(t_token **token);// -> word
t_node *redir_out(t_token **token);// -> word
t_node *word(t_token **token); // -> argument

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
    node->kind = BUILTIN; 
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
    
    last = command->cmds;
    if (command->cmds == NULL) 
    {
        command->cmds = word;
        return ;
    }
    while (last->next != NULL) 
        last = last->next;
    last->next = word;
}

void redir_in_addback(t_node *command, t_node *rdr_in) 
{
    if (command->redir_in == NULL)
    {
        command->redir_in == rdr_in;
        return ;
    }
    t_node *last;
    while (last->next != NULL) 
        last = last->next;
    last->next = redir_in;
}

void redir_out_addback(t_node *command, t_node *rdr_out) 
{
    if (command->redir_out == NULL)
    {
        command->redir_out == rdr_out;
        return ;
    }
    t_node *last;
    while (last->next != NULL) 
        last = last->next;
    last->next = redir_out;
}

//parser    = pipe_cmd EOF
t_node *parser(t_token *token)
{
    t_node *node;

    node = pipe_cmd(&token);
    if (!consume(token, TOKEN_EOF, NULL))
    { 
        printf("parsing error : 'TOKEN_EOF'\n");
        exitt(0);
    }
    token = skip(token, TOKEN_EOF, NULL);
    return (node);
}

//pipe_cmd  = command ("|" command)*
t_node *pipe_cmd(t_token **token)
{
    t_node *node;
    
    node =  new_node_pipe(NULL, command(token));
    if (!consume(token, PIPE, "|"))
        *token = skip(*token, PIPE, "|"); 
    else 
        printf("parsing error : '|'\n");
    node = command(&token);
    return (node);
}

//command   = word (word | redir_in | redir_out)*
/*
**  /!\ il faut modifier boucle while
*/
t_node *command(t_token **token)
{
    t_node *node;
    int res;
    
    res = 0;
    node = new_node_command();
    command_addback(node, word(token));
    while (res == 0)
    {
        res = consume(token, ARGUMENT, NULL);
        if (res == 0)
            command_addback(node, word(token));
        res = consume(token, OP, "<");
        if (res == 0)
            redir_in_addback(node, redir_in(token));
        res = consume(token, OP, "<<");
        if (res == 0)
            redir_in_addback(node, redir_in(token));
        res = consume(token, OP, ">");
        if (res == 0)
            redir_out_addback(node, redir_out(token));
        res = consume(token, OP, ">>");
        if (res == 0)
            redir_out_addback(node, redir_out(token));
        else
            break;
    }
    return (node);
}

//redir_in  = ("<" | "<<") word
t_node *redir_in(t_token **token)
{
    t_node *node;

    node = word(&token);
    if (!consume(token, OP, "<"))
        *token = skip(*token, OP, "<");
    else if (!consume(token, OP, "<<"))
        *token = skip(*token, OP, "<<"); 
    else 
        printf("parsing error : '<' or '<<'\n");
    return (node);
}

//redir_out = (">" | ">>") word
t_node *redir_out(t_token **token)
{
    t_node *node;

    node = word(&token);
    if (!consume(token, OP, ">"))
        *token = skip(*token, OP, ">");
    else if (!consume(token, OP, ">>"))
        *token = skip(*token, OP, ">>"); 
    else 
        printf("parsing error : '>' or '>>'\n");
    return (node);
}

//word      = (e.g.) "ls", "-l", "file", ...
t_node *word(t_token **token)
{
    t_node *node;

    if (!consume(token, ARGUMENT, NULL))
        node = new_node_word(*token);
    token = skip(&token, ARGUMENT, NULL);
    return (node);
}

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