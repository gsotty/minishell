/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_flag_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:37:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 12:46:33 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_printf_erreur(char **cmd, int x, int y)
{
	ft_printf("env: illegal option -- %c\nusage: env [-i] ",
			cmd[x][y]);
	ft_printf("[-u name] [name=value ...]\n\t   [utility [argume");
	ft_printf("nt ...]]\n");
	return (-1);
}

static int	verif_u_min(char **cmd, int x, int y, t_flag_env *flag)
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

static int	verif_flag_env(char **cmd, int x, t_flag_env *flag)
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
				return (verif_u_min(cmd, x, y, flag));
			else
				return (ft_printf_erreur(cmd, x, y));
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

int			check_flag_env(char **cmd, t_flag_env *flag)
{
	int			x;
	int			ret;

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
