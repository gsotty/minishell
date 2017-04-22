/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenvp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:38:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(char **cmd)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		if (ft_strchr(cmd[x], '=') != NULL)
			add_envp(cmd[x]);
		else
		{
			ft_printf_e("\033[31mminishell: setenvp: \033[0m%s", cmd[x]);
			ft_printf_e("\033[31m: invalid argument\n\033[0m");
			return ;
		}
		x++;
	}
	return ;
}
