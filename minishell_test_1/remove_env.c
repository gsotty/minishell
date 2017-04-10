/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 18:04:55 by gsotty           ###   ########.fr       */
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

static int	find_var(char **envp, char *tmp_data, int x)
{
	char	*tmp_envp;
	char	*p;

	tmp_envp = ft_strdup(envp[x]);
	p = ft_strchr(tmp_envp, '=');
	*p = '\0';
	if (ft_strcmp(tmp_envp, tmp_data) == 0)
	{
		free(tmp_envp);
		return (1);
	}
	free(tmp_envp);
	return (0);
}

static char	**ft_remove(char **envp, int x, int len_envp)
{
	if (envp[0] != NULL && envp[1] == NULL)
	{
		free(envp[0]);
		free(envp);
		envp = NULL;
	}
	else
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

static char	**ft_while_remove(char **envp, char *data, int len_envp)
{
	int		x;
	char	*tmp_data;

	x = 0;
	tmp_data = ft_strdup(data);
	while (envp[x] != NULL)
	{
		if ((find_var(envp, tmp_data, x)) == 1)
			break ;
		x++;
	}
	free(tmp_data);
	if (envp[x] != NULL)
		envp = ft_remove(envp, x, len_envp);
	return (envp);
}

char		**remove_env(char **envp, char *data)
{
	int		len_envp;

	len_envp = len_tab(envp);
	if (envp == NULL || data == NULL)
		return (envp);
	else
		return (ft_while_remove(envp, data, len_envp));
}
