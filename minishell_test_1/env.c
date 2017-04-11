/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 13:56:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/11 15:45:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_argv(char **cmd, char **envp, int ret)
{
	int		y;

	y = 0;
	while (cmd[ret + y] != NULL)
	{
		if (ft_strchr(cmd[ret + y], '=') != NULL)
			envp = add_env(envp, cmd[ret + y]);
		else
			break ;
		y++;
	}
	if (cmd[ret + y] != NULL)
	{
		envp = exe_cmd(1, cmd + ret + y, envp);
		y++;
	}
	else if (cmd[ret + y] == NULL)
	{
		cmd[0] = ft_strdup("env");
		cmd[1] = NULL;
		envp = ft_env(cmd, envp);
	}
	return (envp);
}

char	**env_no_argv(char **envp)
{
	int		x;

	x = 0;
	if (envp == NULL || envp[0] == NULL)
		return (envp);
	while (envp[x] != NULL)
	{
		ft_printf("%s\n", envp[x]);
		x++;
	}
	return (envp);
}

char	**ft_env(char **cmd, char **envp)
{
	int				ret;
	t_flag_env		flag;

	ft_memset(&flag, '\0', sizeof(t_flag_env));
	if ((ret = check_flag_env(cmd, &flag, envp)) == -1)
		return (envp);
	if (flag.i_min == 1)
	{
		free_tab(envp);
		envp = NULL;
	}
	if (cmd[ret] == NULL && flag.u_min == 0)
		envp = env_no_argv(envp);
	else
	{
		if (flag.u_min >= 1)
			envp = remove_env(envp, flag.name);
		envp = env_argv(cmd, envp, ret);
	}
	if (flag.u_min == 1)
		free(flag.name);
	return (envp);
}
