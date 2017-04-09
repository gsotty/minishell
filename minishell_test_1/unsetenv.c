/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:49:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 14:50:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unsetenv(char **envp, char **cmd)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		envp = remove_env(envp, cmd[x]);
		x++;
	}
	return (envp);
}
