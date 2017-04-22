/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:08:17 by gsotty           ###   ########.fr       */
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

static int	find_var(char *tmp_data, int x)
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

static void	ft_remove(int x, int len_envp)
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
	return ;
}

static void	ft_while_remove(char *data, int len_envp)
{
	int		x;
	char	*tmp_data;

	x = 0;
	tmp_data = ft_strdup(data);
	while (envp[x] != NULL)
	{
		if ((find_var(tmp_data, x)) == 1)
			break ;
		x++;
	}
	free(tmp_data);
	if (envp[x] != NULL)
		ft_remove(x, len_envp);
	return ;
}

void		remove_envp(char *data)
{
	int		len_envp;

	len_envp = len_tab(envp);
	if (envp == NULL || data == NULL)
		return ;
	else
		return (ft_while_remove(data, len_envp));
}
