/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 13:56:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 17:43:37 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verif_flag_env(char **cmd, int x, t_flag_env *flag)
{
	int		y;

	y = 1;
	if (cmd[x][0] == '-' && cmd[x][1] != '\0')
	{
		while (cmd[x][y] != '\0')
		{
			if (cmd[x][y] == 'i')
				flag->i_min = 1;
			else if (cmd[x][y] == 'u')
			{
				flag->u_min += 1;
				if (cmd[x][y + 1] != '\0')
				{
					flag->name = ft_strdup(cmd[x] + y + 1);
					return (1);
				}
				else if (cmd[x][y + 1] == '\0' && cmd[x + 1] != NULL)
				{
					flag->name = ft_strdup(cmd[x + 1]);
					return (2);
				}
				else
				{
					ft_printf("env: option requires an argument -- %c\nusage:",
							cmd[x][y]);
					ft_printf(" env [-i] [-u name] [name=value ...]");
					ft_printf("\n\t   [utility [argument ...]]\n");
					return (-1);
				}
			}
			else
			{
				ft_printf("env: illegal option -- %c\nusage: env [-i] ",
						cmd[x][y]);
				ft_printf("[-u name] [name=value ...]\n\t   [utility [argume");
				ft_printf("nt ...]]\n");
				return (-1);
			}
			y++;
		}
		return (1);
	}
	else if (cmd[x][0] == '-' && cmd[x][1] == '\0')
		flag->i_min = 1;
	else
		return (0);
	return (1);
}

int		check_flag_env(char **cmd, t_flag_env *flag)
{
	int		x;
	int		ret;

	x = 1;
	while (cmd[x] != NULL)
	{
		if ((ret = verif_flag_env(cmd, x, flag)) == 0)
			break ;
		if (ret == -1)
			return (-1);
		if (ret == 2)
			x++;
		x++;
	}
	return (x);
}

char	**ft_env(char **cmd, char **envp)
{
	int				y;
	int				x;
	int				ret;
	t_flag_env		flag;

	y = 0;
	x = 0;
	if ((ret = check_flag_env(cmd, &flag)) == -1)
		return (envp);
	if (cmd[ret] == NULL && flag.u_min == 0)
	{
		if (flag.i_min == 0)
		{
			while (envp[x] != NULL)
			{
				ft_printf("%s\n", envp[x]);
				x++;
			}
		}
	}
	else
	{
		if (flag.i_min == 1)
			envp = NULL;
		if (flag.u_min == 1)
			envp = remove_env(envp, flag.name);
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
			free_tab(cmd);
			cmd[0] = ft_strdup("env");
			cmd[1] = NULL;
			envp = ft_env(cmd, envp);
		}
	}
	return (envp);
}
