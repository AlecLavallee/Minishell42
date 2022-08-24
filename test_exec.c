/*   /!\ cette partie j'ai reference un example
et j'ai change tous les variables pour adapter ma propore version

** NB : 08/21 my echo can work!

*/

extern int exit_status;

#include "./inc/minishell.h"


/*
originnal alelaval's fonction
I changed for adaptation
*/
void	exec_builtin(t_node *node, t_shell *shell)
{
    t_cmd *command;

    command = node->cmds;

	if (!ft_strncmp(command->word->str, "echo", ft_strlen(command->word->str)))
		 exit_status = echo(command->word);
    else if (!ft_strncmp(command->word->str, "env", ft_strlen(command->word->str)))
		 exit_status = env(command->word, shell);
	else if (!ft_strncmp(command->word->str, "pwd", ft_strlen(command->word->str)))
		 exit_status = pwd(command->word);
	else if (!ft_strncmp(command->word->str, "cd", ft_strlen(command->word->str)))
		 exit_status = cd(command->word, shell);
	else if (!ft_strncmp(command->word->str, "export", ft_strlen(command->word->str)))
		 exit_status = export(command->word, shell);
	else if (!ft_strncmp(command->word->str, "unset", ft_strlen(command->word->str)))
		 exit_status = unset(command->word, shell);
	//if (!ft_strncmp(shell->cmds->args[0], "pwd", ft_strlen(shell->cmds->args[0])))
	//	pwd();
    else
    {
        ft_putstr_fd("no match command\n", 2);
        exit(1);
    }
}

/*void	exec_builtin(t_node *node)
{
	t_cmd		*cmd;
	long		i;
	static	int	(*builtin_fn[])(t_word *) = {
		builtin_echo, builtin_cd, builtin_pwd, builtin_export,
		builtin_unset, builtin_env, builtin_exit, NULL};
	static char	*kw[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	cmd = node->cmds;
	i = 0;
	while (kw[i])
	{
		if (strcmp(kw[i], cmd->word->str) == 0)
		{
			global_shell->exit_status = builtin_fn[i](cmd->word);
			break ;
		}
		i++;
	}
	if (kw[i] == NULL)
		printf("no match builtin"); 
}
*/

bool	set_redir_in(t_redir *redir_in)
{
	int	fd;

	if (redir_in == NULL)
		return (true);
	fd = -1;
	if (redir_in->kind == REDIR_IN)
	{
		fd = open(redir_in->str, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd("redir_in->str", 2); 
            ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	else if (redir_in->kind == REDIR_HEREDOC)
		fd = redir_in->fd;
	else
    {
		ft_putstr_fd("error: set_redir_in()", 2);
        exit(1);
    }
	dup2(fd, 0);
	close(fd);
	return (set_redir_in(redir_in->next));
}

bool	set_redir_out(t_redir *redir_out)
{
	int	fd;
	int	oflag;

	if (redir_out == NULL)
		return (true);
	oflag = 0;
	if (redir_out->kind == REDIR_OUT)
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir_out->kind == REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
    {
		ft_putstr_fd("error: set_redir_out()", 2);
        exit(1);
    }
	fd = open(redir_out->str, oflag, 0664);
	if (fd < 0)
	{
		printf("minishell: %s: \n", redir_out->str); //+error
		return (false);
	}
	dup2(fd, 1);
	close(fd);
	return (set_redir_out(redir_out->next));
}

int	fail_exec(t_node *node)
{
	exit_status = 126;
	if (errno == ENOENT)
		exit_status = 127;
	ft_putstr_fd("minishell: ", 1);
 	ft_putstr_fd(node->cmds->pathname, 1);
	ft_putstr_fd("\n", 1);   
	return (exit_status);
}

bool	is_directory(char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

char	**create_argv(t_word *word)
{
	char	**argv;
	long	len;
	t_word	*now;
	long	i;

	len = 0;
	now = word;
	while (now)
	{
		len++;
		now = now->next;
	}
	argv = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (word)
	{
		argv[i] = word->str;
		i++;
		word = word->next;
	}
	return (argv);
}


int	check_cmd(t_cmd *cmd)
{
	if (cmd->pathname == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->word->str, 2);
        ft_putstr_fd(" command not found\n", 2);
		exit_status = 127;
		return (1);
	}
	if (is_directory(cmd->pathname))
	{
		//printf("minishell: %s: is a directory\n", cmd->pathname); 
        ft_putstr_fd("minishell:", 2);
        ft_putstr_fd(cmd->pathname, 2);
        ft_putstr_fd(" is a directory\n", 2);
		exit_status = 126;
		return (1);
	}
	return (0);
}

void	set_exit_status(void)
{
	if (WIFSIGNALED(exit_status))
	{
		exit_status = 128 + WTERMSIG(exit_status);
		if (exit_status == 128 + SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
	else
		exit_status = WEXITSTATUS(exit_status);
}

void	exec_file(t_node *node, t_shell *shell)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;
	int exit_status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (check_cmd(node->cmds))
			exit(exit_status);
		cmd_argv = create_argv(node->cmds->word);
		cmd_envp = create_envp(shell);
		execve(node->cmds->pathname, cmd_argv, cmd_envp);
		free(cmd_argv);
		free_envp(cmd_envp);
		exit(fail_exec(node));
	}
	waitpid(pid, &(exit_status), 0);
	set_exit_status();
}

void	exec_cmd(t_node *node, t_shell *shell)
{
	//if (interrupt)
	//	return ;
	if (!set_redir_in(node->cmds->redir_in)
		|| !set_redir_out(node->cmds->redir_out)
		|| node->cmds->word == NULL)
	{
		dup2(shell->fdin, 1);
		dup2(shell->fdout, 0);
		exit_status = 1;
		return ;
	}
	if (node->cmds->is_builtin)
		exec_builtin(node, shell);
	else
		exec_file(node, shell);
	dup2(shell->fdout, 1);
	dup2(shell->fdin, 0);
}

void	exec_no_pipe(t_node *pipe_node, t_shell *shell)
{
	exec_cmd(pipe_node->rhs, shell);
}

void	exec_multi_pipes(t_node *pipe_node, t_shell *shell)
{
	int	fd[2];
	int	pid;

	if (pipe_node == NULL)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (pipe_node->lhs)
			dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		    exec_cmd(pipe_node->rhs, shell);
		exit(exit_status);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		exec_multi_pipes(pipe_node->lhs, shell);
	}
	waitpid(pid, &(exit_status), 0);
	exit_status = WEXITSTATUS(exit_status);
}

void	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pid;
	int	sts;

	expander(pipe_node, shell);
	if (pipe_node->lhs == NULL)
		exec_no_pipe(pipe_node, shell);// go testfile
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_multi_pipes(pipe_node, shell); // go testfile
			exit(exit_status);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		exit_status = WEXITSTATUS(sts);
	}
}