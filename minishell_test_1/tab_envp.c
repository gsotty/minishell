/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 19:11:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**creat_envp(char **envp)
{
	int		x;
	char	**new_envp;

	x = 0;
	while (envp[x] != NULL)
		x++;
	if ((new_envp = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (envp[x] != NULL)
	{
		new_envp[x] = ft_strdup(envp[x]);
		x++;
	}
	return (new_envp);
}

char	**remalloc_envp(char **envp, int after_size, int new_size)
{
	int		x;
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x <= after_size)
	{
		new_envp[x] = ft_strdup(envp[x]);
		free(envp[x]);
		x++;
	}
	free(envp);
	return (new_envp);
}
