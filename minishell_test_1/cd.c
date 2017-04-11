/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/11 16:03:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_pwd(char **envp)
{
	char	pwd[PATH_MAX + 1];

	getcwd(pwd, PATH_MAX);
	envp = add_env(envp, ft_strjoin("PWD=", pwd));
	return (envp);
}

char	**cd_no_argv(char **envp)
{
	char	*tmp;
	char	pwd[PATH_MAX + 1];

	if ((tmp = find_var_env(envp, "HOME")) == NULL)
	{
		ft_printf_e("\033[31mcd: HOME not set\033[0m\n");
		return (envp);
	}
	getcwd(pwd, PATH_MAX);
	envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
	if (chdir(tmp) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n", tmp);
		return (envp);
	}
	envp = add_pwd(envp);
	return (envp);
}

char	**cd_argv(char **argv, char **envp)
{
	char	pwd[PATH_MAX + 1];

	getcwd(pwd, PATH_MAX);
	envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
	if (chdir(argv[1]) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n",
				argv[1]);
		return (envp);
	}
	envp = add_pwd(envp);
	return (envp);
}

char	**cd_argv_neg(char **envp)
{
	char	*tmp;
	char	pwd[PATH_MAX + 1];

	if ((tmp = find_var_env(envp, "OLDPWD")) == NULL)
	{
		ft_printf_e("\033[31mcd: OLDPWD not set\033[0m\n");
		return (envp);
	}
	getcwd(pwd, PATH_MAX);
	envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
	ft_printf("%s\n", tmp);
	if (chdir(tmp) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n", tmp);
		return (envp);
	}
	envp = add_pwd(envp);
	return (envp);
}

char	**cd(char **argv, char **envp)
{
	if (argv[1] == NULL)
		envp = cd_no_argv(envp);
	else if (argv[1][0] == '-' && argv[1][1] == '\0' && argv[2] == '\0')
		envp = cd_argv_neg(envp);
	else if (argv[1] != '\0' && argv[2] == '\0')
		envp = cd_argv(argv, envp);
	else
		ft_printf_e("\033[31mcd: string not in pwd:\033[0m %s\n", argv[1]);
	return (envp);
}
