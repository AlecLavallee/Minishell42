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

#include "../../inc/minishell.h"

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
//t_node *stmt(t_token **token);
t_node *parser(t_token *token); // -> pipe_cmd
t_node *stmt(t_token **token);
t_node *pipe_cmd(t_token **token);// -> command
t_node *command(t_token **token);// -> word | redir_in | redir_out
//t_node *redir_in(t_token **token);// -> word
//t_node *redir_out(t_token **token);// -> word
t_node *word(t_token **token); // -> argument


//parser    = pipe_cmd EOF
t_node *parser(t_token *token)
{
     t_node *node;

    node = pipe_cmd(&token);
    token = skip(token, TOKEN_EOF, NULL);
    return (node);
}   


//pipe_cmd  = command ("|" command)*
t_node *pipe_cmd(t_token **token)
{
    t_node *node;
    
    node =  new_node_pipe(command(token));
    while (!consume(*token, TOKEN_PIPE, "|"))
    {
        *token = skip(*token, TOKEN_PIPE, "|");
        node  = add_node_pipe(node, command(token));
    } 
    return (node);
}

//command   = word (word | redir_in | redir_out)*
/*
** 
*/


//redir_in  = ("<" | "<<") word
void redir_in(t_token **token, t_node *node)
{
    //t_node *node;
    //node = word(token);
    if (!consume(*token, TOKEN_OP, "<"))
    {
        *token = skip(*token, TOKEN_OP, "<");
        redir_in_addback(node->cmds, REDIR_IN, (*token)->string, (*token)->len);
    }
    else if (!consume(*token, TOKEN_OP, "<<"))
    {
        *token = skip(*token, TOKEN_OP, "<<");
        redir_in_addback(node->cmds, REDIR_HEREDOC, (*token)->string, (*token)->len);
    } 
    else 
        printf("parsing error : '<' or '<<'\n");
    //node = word(token);
    //return (node);
}

//redir_out = (">" | ">>") word
void redir_out(t_token **token, t_node *node)
{
    //t_node *node;

    if (!consume(*token, TOKEN_OP, ">"))
    {
        *token = skip(*token, TOKEN_OP, ">");
        redir_out_addback(node->cmds, REDIR_OUT, (*token)->string, (*token)->len);
    }
    else if (!consume(*token, TOKEN_OP, ">>"))
    {
        *token = skip(*token, TOKEN_OP, ">>");
        redir_out_addback(node->cmds, REDIR_APPEND, (*token)->string, (*token)->len);
    } 
    else 
        printf("parsing error : '>' or '>>'\n");
    //node = word(token);
    //return (node);
}

t_node *command(t_token **token)
{
    t_node *node;

    node = new_node_command();
    //command_addback(node, word(token));
    while (1)
    {
        if (!consume(*token, TOKEN_ARGUMENT, NULL))
            word_addback(node->cmds, (*token)->string, (*token)->len);
        else if (!consume(*token, TOKEN_OP, "<") || !consume(*token, TOKEN_OP, "<<"))
            redir_in(token, node);
        else if (!consume(*token, TOKEN_OP, ">") || !consume(*token, TOKEN_OP, ">>"))
            redir_out(token, node);
            
        else
        {
            if (node->cmds->word == NULL && node->cmds->redir_in == NULL
                && node->cmds->redir_out == NULL)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token \n", 2);
                exit(1);
            }
            return (node);
        }
        *token = skip(*token, TOKEN_ARGUMENT, NULL); 
    }
    return (node);
}

/*
t_node *command(t_token **token)
{
    t_node *node;
    int res = 0;

    node = new_node_command();
    command_addback(node, word(token));
    while (res == 0)
    {
        if ((res = consume(*token, TOKEN_ARGUMENT, NULL)) == 0)
            command_addback(node, word(token));
        else if ((res = consume(*token, TOKEN_OP, "<")) == 0 
            || (res = consume(*token, TOKEN_OP, "<<")) == 0)
            redir_in_addback(node, redir_in(token));
        else if ((res = consume(*token, TOKEN_OP, ">")) == 0 
            || (res = consume(*token, TOKEN_OP, ">>")) == 0)
            redir_out_addback(node, redir_out(token));
        else
            break;
    }
    return (node);
}
*/



/*
//word      = (e.g.) "ls", "-l", "file", ...
t_node *word(t_token **token)
{
    t_node *node;

    if (!consume(*token, TOKEN_ARGUMENT, NULL))
        node = new_node_word(*token);
    *token = skip(*token, TOKEN_ARGUMENT, NULL);
    return (node);
}*/