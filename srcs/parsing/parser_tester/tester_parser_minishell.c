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

    char *str = "ls -l | cat << file";
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
            printf("---PIPE---\n");
        }
        debug_parser_recursive(node->rhs);
    }

    if (node->kind == COMMAND) 
    {
            if (node->cmds->word) 
            {
                printf("COMMAND   :");
                t_word *word = node->cmds->word;
                while (word)
                {
                    printf("'%s' ", word->str);
                    word = word->next;
                }
            }
            printf("\n");
            
            if (node->cmds->redir_in)
            {
                if (node->cmds->redir_in->kind == REDIR_IN)
                    printf("REDIR_IN : ");
                else
                    printf("HEREDOC : ");
                t_redir *rdr_in = node->cmds->redir_in;
                while (rdr_in) 
                {
                    printf("'%s' ", rdr_in->str);
                    rdr_in = rdr_in->next;
                }
                printf("\n");
            }
            if (node->cmds->redir_out) 
            {
                if (node->cmds->redir_out->kind == REDIR_OUT) 
                    printf("REDIR_OUT: ");
                else
                    printf("REDIR_APPRND : ");
                t_redir *rdr_out = node->cmds->redir_out;
                while (rdr_out) 
                {
                    printf("'%s' ", rdr_out->str);
                    rdr_out = rdr_out->next;
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