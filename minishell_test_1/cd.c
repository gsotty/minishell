/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 15:42:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_pwd(char **envp)
{
	char	pwd[PATH_MAX + 1];
	int		len_pwd;

	getcwd(pwd, PATH_MAX);
	len_pwd = ft_strlen(pwd);
	pwd[len_pwd] = '/';
	pwd[len_pwd + 1] = '\0';
	envp = add_env(envp, ft_strjoin("PWD=", pwd));
	return (envp);
}

char	**cd(char **argv, char **envp)
{
	char	*tmp;
	char	pwd[PATH_MAX + 1];

	if (argv[1] == NULL)
	{
		tmp = find_var_env(envp, "HOME");
		getcwd(pwd, PATH_MAX);
		if (chdir(tmp) == -1)
		{
			ft_printf("error\n");
			return (envp);
		}
		envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
		envp = add_pwd(envp);
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0' &&  argv[2] == '\0')
	{
		tmp = find_var_env(envp, "OLDPWD");
		getcwd(pwd, PATH_MAX);
		if (chdir(tmp) == -1)
		{
			ft_printf("error\n");
			return (envp);
		}
		envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
		envp = add_pwd(envp);
	}
	else if (argv[1] != '\0' && argv[2] == '\0')
	{
		if (argv[1][0] == '/')
		{
			getcwd(pwd, PATH_MAX);
			if (chdir(argv[1]) == -1)
			{
				ft_printf("error\n");
				return (envp);
			}
			envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
			envp = add_pwd(envp);
		}
		else
		{
			getcwd(pwd, PATH_MAX);
			envp = add_env(envp, ft_strjoin("OLDPWD=", pwd));
			if (chdir(argv[1]) == -1)
			{
				ft_printf("error\n");
				return (envp);
			}
			envp = add_pwd(envp);
		}
	}
	else
		ft_printf("cd: string not in pwd: %s\n", argv[1]);
	return (envp);
}
