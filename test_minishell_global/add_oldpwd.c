/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_oldpwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:53:14 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 14:55:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_oldpwd(t_flag_cd *flag_cd, char *path)
{
	char			*tmp_pwd;
	char			pwd[PATH_MAX + 1];
	struct stat		lg;
	struct stat		phy;

	if (flag_cd->p_maj == 1)
	{
		getcwd(pwd, PATH_MAX);
		tmp_pwd = ft_strjoin("OLDPWD=", pwd);
		add_env(tmp_pwd);
		free(tmp_pwd);
	}
	else
	{
		if (path != NULL && *path == '/')
		{
			if (stat(path, &lg) == -1 || stat(".", &phy) == -1)
			{
				getcwd(pwd, PATH_MAX);
				tmp_pwd = ft_strjoin("OLDPWD=", pwd);
				add_env(tmp_pwd);
				free(tmp_pwd);
			}
			if (lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
			{
				tmp_pwd = ft_strjoin("OLDPWD=", path);
				add_env(tmp_pwd);
				free(tmp_pwd);
			}
		}
		else
		{
			getcwd(pwd, PATH_MAX);
			tmp_pwd = ft_strjoin("OLDPWD=", pwd);
			add_env(tmp_pwd);
			free(tmp_pwd);
		}
	}
	return ;
}

