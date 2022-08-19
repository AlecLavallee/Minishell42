#include "../../../inc/minishell.h"
void test(void);
void debug_parser(t_node *node);
void debug_parser_recursive(t_node *node);


int main()
{
    test();
    return (0);
}


void test(void)
{
    t_command *token;
    t_node *node;

    char *str = "echo hello > file ";
    token = lexer(str);
    node = parser(token->first_token);
    if (node == NULL)
        printf("node error\n");
    debug_parser_recursive(node);
    free_command_line(token);
    free_node(node);
}


void debug_parser_recursive(t_node *node) 
{
    if (node == NULL)
        return;
    
    if (node->kind == PIPE) 
    {
        if (node->lhs != NULL) 
        {
            debug_parser_recursive(node->lhs);
            printf("---Pipe---\n");
        }
        debug_parser_recursive(node->rhs);
    }

    if (node->kind == COMMAND) 
    {
        printf("cmds   :");
        t_node *cmd = node;
        while (cmd) 
        {
            printf("'%s' ", cmd->cmds->word->str);
            cmd = node->next;
        }
        printf("\n");
        if (node->redir_in)
        {
            printf("redir_in : ");
            t_node *rdr_in = node;
            while (rdr_in) 
            {
                printf("'%s' ", rdr_in->redir_in->str);
                rdr_in = node->next;
            }
            printf("\n");
        }
        if (node->redir_out) 
        {
            printf("redir_out: ");
            t_node *rdr_out = node;
            while (rdr_out) 
            {
                printf("'%s' ", rdr_out->redir_out->str);
                rdr_out = redir_out->next;
            }
            printf("\n");
        }
    }
}
/*
void debug_parser(t_node *node) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("---parser start---\n");
    debug_parser_recursive(node);
}*/