#include "../inc/minishell.h"
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

    char *str = "echo hello | file";
    token = lexer(str);
    node = parser(token->first_token);
    if (node == NULL)
        printf("node error\n");
    
    debug_parser_recursive(node);
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
        debug_parser_recursive(ngit lode->rhs);
    }

    if (node->kind == COMMAND) 
    {
        printf("cmds   :");
        t_node *cmd = node->cmds;
        while (cmd) 
        {
            printf("'%s' ", cmd->str);
            cmd = cmd->next;
        }
        printf("\n");
        if (node->redir_in)
        {
            printf("redir_in : ");
            t_node *redir_in = node->redir_in;
            while (redir_in) 
            {
                printf("'%s' ", redir_in->str);
                redir_in = redir_in->next;
            }
            printf("\n");
        }
        if (node->redir_out) 
        {
            printf("redir_out: ");
            t_node *redir_out = node->redir_out;
            while (redir_out) 
            {
                printf("'%s' ", redir_out->str);
                redir_out = redir_out->next;
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