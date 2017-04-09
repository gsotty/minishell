/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:34:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 19:38:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	len_tab(char	**tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
		x++;
	return (x);
}
*/

char		**add_env(char **envp, char *data)
{
	int		x;
	char	*p;
	char	*tmp_data;
	char	*tmp_envp;

	x = 0;
	tmp_data = ft_strdup(data);
	p = ft_strchr(tmp_data, '=');
	*p = '\0';
	while (envp[x + 1] != NULL)
	{
		tmp_envp = ft_strdup(envp[x]);
		p = ft_strchr(tmp_envp, '=');
		*p = 0;
		if (ft_strcmp(tmp_envp, tmp_data) == 0)
		{
			free(tmp_envp);
			break ;
		}
		free(tmp_envp);
		x++;
	}
	if (envp[x + 1] == NULL)
	{
		envp = remalloc_envp(envp, x, x + 1);
		envp[x + 1] = ft_strdup(data);
	}
	else
	{
		free(envp[x]);
		envp[x] = ft_strdup(data);
	}
	free(tmp_data);
	return (envp);
}
