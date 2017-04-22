/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:36:39 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd(void)
{
	char	*tmp_pwd;
	char	pwd[PATH_MAX + 1];

	getcwd(pwd, PATH_MAX);
	tmp_pwd = ft_strjoin("PWD=", pwd);
	add_envp(tmp_pwd);
	free(tmp_pwd);
	return ;
}

void	cd_no_argv(void)
{
	char	*tmp;
	char	*tmp_join;
	char	pwd[PATH_MAX + 1];

	if ((tmp = find_var_env("HOME")) == NULL)
	{
		ft_printf_e("\033[31mcd: HOME not set\033[0m\n");
		return ;
	}
	getcwd(pwd, PATH_MAX);
	tmp_join = ft_strjoin("OLDPWD=", pwd);
	add_envp(tmp_join);
	free(tmp_join);
	if (chdir(tmp) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n", tmp);
		return ;
	}
	add_pwd();
	return ;
}

void	cd_argv(char **argv, t_flag_cd *flag_cd, int x)
{
	char			pwd[PATH_MAX + 1];
	char			*tmp_join;
	char			*buf;
	int				fd;

	fd = 0;
	if ((buf = ft_memalloc(sizeof(buf) * 255)) == NULL)
		return ;
	getcwd(pwd, PATH_MAX);
	tmp_join = ft_strjoin("OLDPWD=", pwd);
	add_envp(tmp_join);
	free(tmp_join);
	if (chdir(argv[x]) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n",
				argv[x]);
		return ;
	}
	if (flag_cd->p_maj == 1)
		add_envp(ft_strjoin("PWD=", argv[x]));
	else if (flag_cd->l_maj == 1)
		add_pwd();
	else
		add_pwd();
	return ;
}

void	cd_argv_neg(void)
{
	char	*tmp;
	char	*tmp_join;
	char	pwd[PATH_MAX + 1];

	if ((tmp = find_var_env("OLDPWD")) == NULL)
	{
		ft_printf_e("\033[31mcd: OLDPWD not set\033[0m\n");
		return ;
	}
	getcwd(pwd, PATH_MAX);
	tmp_join = ft_strjoin("OLDPWD=", pwd);
	add_envp(tmp_join);
	free(tmp_join);
	ft_printf("%s\n", tmp);
	if (chdir(tmp) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n", tmp);
		return ;
	}
	add_pwd();
	return ;
}

int		check_flag_cd(t_flag_cd *flag_cd, char **argv)
{
	int		x;

	x = 0;
	if (argv[1] == NULL)
	{
		flag_cd->rien = 1;
		return (x);
	}
	else if (ft_strcmp(argv[1], "-L") == 0)
	{
		flag_cd->l_maj = 1;
		x++;
	}
	else if (ft_strcmp(argv[1], "-P") == 0)
	{
		flag_cd->p_maj = 1;
		x++;
	}
	else if (ft_strcmp(argv[1], "-") == 0)
		flag_cd->neg = 1;
	if (!(argv[x + 1] != '\0' || argv[x + 2] == '\0'))
	{
		ft_printf_e("\033[31mcd: string not in pwd:\033[0m %s\n", argv[x + 1]);
		return (-1);
	}
	return (x);
}

void	cd(char **argv)
{
	int			x;
	t_flag_cd	flag_cd;

	x = 0;
	ft_memset(&flag_cd, '\0', sizeof(flag_cd));
	if ((x = check_flag_cd(&flag_cd, argv)) == -1)
		return ;
	if (flag_cd.rien == 1)
		cd_no_argv();
	else if (flag_cd.neg == 1)
		cd_argv_neg();
	else
		cd_argv(argv, &flag_cd, x + 1);
	return ;
}
