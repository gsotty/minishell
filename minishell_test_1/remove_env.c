/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 19:43:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_tab(char **tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
		x++;
	return (x);
}

char		**remove_env(char **envp, char *data)
{
	int		x;
	int		len_envp;
	char	*p;
	char	*tmp_data;
	char	*tmp_envp;

	x = 0;
	len_envp = len_tab(envp);
	if (envp == NULL || data == NULL)
		return (envp);
	else
	{
		tmp_data = ft_strdup(data);
		while (envp[x] != NULL)
		{
			tmp_envp = ft_strdup(envp[x]);
			p = ft_strchr(tmp_envp, '=');
			*p = '\0';
			if (ft_strcmp(tmp_envp, tmp_data) == 0)
			{
				free(tmp_envp);
				break ;
			}
			free(tmp_envp);
			x++;
		}
		if (envp[x] != NULL)
		{
			while (x < len_envp)
			{
				free(envp[x]);
				if (envp[x + 1] != NULL)
					envp[x] = ft_strdup(envp[x + 1]);
				else
					envp[x] = NULL;
				x++;
			}
		}
		return (envp);
	}
}
