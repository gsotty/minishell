/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:28:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:31:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_argv(char **cmd, int ret)
{
	int		y;

	y = 0;
	while (cmd[ret + y] != NULL)
	{
		if (ft_strchr(cmd[ret + y], '=') != NULL)
			add_envp(cmd[ret + y]);
		else
			break ;
		y++;
	}
	if (cmd[ret + y] != NULL)
	{
		exe_cmd(1, cmd + ret + y);
		y++;
	}
	else if (cmd[ret + y] == NULL)
	{
		cmd[0] = ft_strdup("env");
		cmd[1] = NULL;
		ft_env(cmd);
	}
	return ;
}

void	env_no_argv(void)
{
	int		x;

	x = 0;
	if (envp == NULL || envp[0] == NULL)
		return ;
	while (envp[x] != NULL)
	{
		ft_printf("%s\n", envp[x]);
		x++;
	}
	return ;
}

void	ft_env(char **cmd)
{
	int				ret;
	t_flag_env		flag;

	ft_memset(&flag, '\0', sizeof(t_flag_env));
	if ((ret = check_flag_env(cmd, &flag)) == -1)
		return ;
	if (flag.i_min == 1)
	{
		free_tab(envp);
		envp = NULL;
	}
	if (cmd[ret] == NULL && flag.u_min == 0)
		env_no_argv();
	else
	{
		if (flag.u_min >= 1)
			remove_envp(flag.name);
		env_argv(cmd, ret);
	}
	if (flag.u_min == 1)
		free(flag.name);
	return ;
}
