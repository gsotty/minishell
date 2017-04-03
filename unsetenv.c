/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:49:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 16:47:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_unsetenv(t_env *begin_env, char **cmd)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		ft_printf("%s\n", cmd[x]);
		begin_env = remove_env(begin_env, cmd[x]);
		x++;
	}
	return (begin_env);
}
