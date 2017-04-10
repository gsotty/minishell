/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 15:12:45 by gsotty           ###   ########.fr       */
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
			ft_printf("minishell: setenv: %s: invalid argument\n", cmd[x]);
			return (envp);
		}
		x++;
	}
	return (envp);
}
