/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:16:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**creat_envp(char **envp_begin)
{
	int		x;

	x = 0;
	if (envp_begin == NULL || envp_begin[0] == NULL)
		return (NULL);
	while (envp_begin[x] != NULL)
		x++;
	if ((envp = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (envp_begin[x] != NULL)
	{
		envp[x] = ft_strdup(envp_begin[x]);
		x++;
	}
	return (envp);
}

void	remalloc_envp(int after_size, int new_size)
{
	int		x;
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		new_envp[x] = ft_strdup(envp[x]);
		free(envp[x]);
		envp[x] = NULL;
		x++;
	}
	free(envp);
	if ((envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		envp[x] = ft_strdup(new_envp[x]);
		free(new_envp[x]);
		new_envp[x] = NULL;
		x++;
	}
	free(new_envp);
	return ;
}
