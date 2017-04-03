/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 15:59:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_setenv(t_env *begin_env, char **cmd)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		if (ft_strchr(cmd[x], '=') != NULL)
			begin_env = add_env(begin_env, cmd[x]);
		else
		{
			ft_printf("minishell: setenv: %s: invalid argument\n", cmd[x]);
			return (1);
		}
		x++;
	}
	return (0);
}
