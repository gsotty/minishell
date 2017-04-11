/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/11 12:42:22 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_setenv(char **envp, char **cmd)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		if (ft_strchr(cmd[x], '=') != NULL)
			envp = add_env(envp, cmd[x]);
		else
		{
			ft_printf_e("\033[31mminishell: setenv: \033[0m%s", cmd[x]);
			ft_printf_e("\033[31m: invalid argument\n\033[0m");
			return (envp);
		}
		x++;
	}
	return (envp);
}
