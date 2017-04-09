/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:10:43 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 15:37:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var_env(char **envp, char *name)
{
	int		x;
	char	*p;
	char	*tmp;

	x = 0;
	while (envp[x] != NULL)
	{
		tmp = ft_strdup(envp[x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		if (ft_strcmp(tmp, name) == 0)
			break ;
		free(tmp);
		x++;
	}
	return (p + 1);
}
