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

t_token *skip(t_token *tok, t_token_kind kind, char *str) 
{
	if (tok->kind != kind)
		printf("skip error : unexpected kind\n");//error
	if (str != NULL && ft_strncmp(tok->string, str, tok->len))
		printf("skip error : unexpectrd str\n");//error
	return tok->next;
}

t_node *parser(t_token *tok);
t_node *pipe_cmd(t_token **tok);
t_node *command(t_token **tok);
t_node *redir_in(t_token **tok);
t_node *redir_out(t_token **tok);
t_node *word(t_token **tok);

void free_node(t_node *node) {
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