/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:34:32 by msuji             #+#    #+#             */
/*   Updated: 2022/08/22 16:34:37 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int go_home(t_shell *shell)
{
    char *home;

    home =  get_env_body("HOME", shell);
    if (home == NULL)
    {
        ft_putstr_fd("Home not find\n", 2);
        return (1);
    }
    if (chdir(home) != 0)
    {
        ft_putstr_fd("minishell:  cd: ", 2);
        ft_putstr_fd(home, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    return (0);
}

void    after_cd(t_shell *shell)
{
    char buff[PATH_MAX];
    t_env env;

    char  *new;
    new = get_env_body("PWD", shell);
    if (getcwd(buff, PATH_MAX))
    {
        ft_strjoin_and_free("OLDPWD=", new);
        env_addback(,"PWD", buffer);
    }
    /*
    ft_memset(buff, 0, PATH_MAX);
	if (!getcwd(buff, PATH_MAX))
	perror("pwd");
	ft_putendl_fd(buff, 1);

    */
}

int cd(t_word *word, t_shell *shell)
{
	char buff[PATH_MAX];

    if (word->next == NULL)
    {
        return (go_home(shell));
    }
    if (chdir(word->next->str) != 0)
    {
        ft_putstr_fd("minishell:  cd: ", 2);
        ft_putstr_fd(word->next->str, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
        //operation apres cd
        /*ft_memset(buff, 0, PATH_MAX); //initialization for variable
	    if (!getcwd(buff, PATH_MAX))
		perror("pwd");
	    ft_putendl_fd(buff, 1);*/
    return (0);
}
