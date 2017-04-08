/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/07 16:59:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_pwd(t_env *env)
{
	char	pwd[PATH_MAX + 1];
	int		len_pwd;

	getcwd(pwd, PATH_MAX);
	len_pwd = ft_strlen(pwd);
	pwd[len_pwd] = '/';
	pwd[len_pwd + 1] = '\0';
	env = add_env(env, ft_strjoin("PWD=", pwd));
	return (env);
}

char	**cd(char **argv, char **envp)
{
	t_env	*env;
	t_env	*tmp_env;
	char	pwd[PATH_MAX + 1];

	env = creat_t_env(envp);
	if (argv[1] == NULL)
	{
		tmp_env = find_var_env(env, "HOME");
		getcwd(pwd, PATH_MAX);
		if (chdir(tmp_env->data) == -1)
		{
			ft_printf("error\n");
			envp = creat_char_envp(env);
			return (envp);
		}
		env = add_env(env, ft_strjoin("OLDPWD=", pwd));
		env = add_pwd(env);
		tmp_env = find_var_env(env, "OLDPWD");
		tmp_env = find_var_env(env, "PWD");
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0' &&  argv[2] == '\0')
	{
		tmp_env = find_var_env(env, "OLDPWD");
		getcwd(pwd, PATH_MAX);
		if (chdir(tmp_env->data) == -1)
		{
			ft_printf("error\n");
			envp = creat_char_envp(env);
			return (envp);
		}
		env = add_env(env, ft_strjoin("OLDPWD=", pwd));
		env = add_pwd(env);
	}
	else if (argv[1] != '\0' && argv[2] == '\0')
	{
		if (argv[1][0] == '/')
		{
			getcwd(pwd, PATH_MAX);
			if (chdir(argv[1]) == -1)
			{
				ft_printf("error\n");
				envp = creat_char_envp(env);
				return (envp);
			}
			env = add_env(env, ft_strjoin("OLDPWD=", pwd));
			env = add_pwd(env);
		}
		else
		{
			getcwd(pwd, PATH_MAX);
			env = add_env(env, ft_strjoin("OLDPWD=", pwd));
			if (chdir(argv[1]) == -1)
			{
				ft_printf("error\n");
				envp = creat_char_envp(env);
				return (envp);
			}
			env = add_pwd(env);
		}
	}
	else
		ft_printf("cd: string not in pwd: %s\n", argv[1]);
	envp = creat_char_envp(env);
	return (envp);
}
