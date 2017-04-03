/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 17:56:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*cd(t_env *env, char **argv)
{
	t_env	*tmp_env;
	char	*p;
	char	*pwd;
	char	*tmp_join;

	if (argv[1][0] == '-' && argv[1][1] == '\0' && argv[2] == '\0')
	{
		tmp_env = env;
		while (tmp_env != NULL)
		{
			if (ft_strcmp(tmp_env->name, "OLDPWD") == 0)
				break ;
			tmp_env = tmp_env->next;
		}
		if ((pwd = ft_memalloc(32764)) == NULL)
			return (env);
		getcwd(pwd, 32764);
		ft_printf("%s\n", tmp_env->data);
		if (chdir(tmp_env->data) == -1)
		{
			ft_printf("error\n");
			return (env);
		}
		env = add_env(env, ft_strjoin("OLDPWD=", pwd));
		free(pwd);
		if ((pwd = ft_memalloc(32764)) == NULL)
			return (env);
		getcwd(pwd, 32764);
		p = ft_strrchr(pwd, '/');
		*p = '\0';
		env = add_env(env, ft_strjoin("PWD=", pwd));
	}
	else if (argv[1] != '\0' && argv[2] == '\0')
	{
		if ((pwd = ft_memalloc(32764)) == NULL)
			return (env);
		getcwd(pwd, 32764);
		env = add_env(env, ft_strjoin("OLDPWD=", pwd));
		p = ft_strrchr(pwd, '/');
		p = p + 1;
		*p = '\0';
		tmp_join = ft_strjoin(pwd, argv[1]);
		if (chdir(tmp_join) == -1)
		{
			ft_printf("error\n");
			return (env);
		}
		free(pwd);
		if ((pwd = ft_memalloc(32764)) == NULL)
			return (env);
		getcwd(pwd, 32764);
		p = ft_strrchr(tmp_join, '/');
		*p = '\0';
		env = add_env(env, ft_strjoin("PWD=", tmp_join));
	}
	else
		ft_printf("cd: string not in pwd: %s\n", argv[1]);
	return (env);
}
