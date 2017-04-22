/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:34:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_var(char *tmp_data)
{
	int		x;
	char	*p;
	char	*tmp_envp;

	x = 0;
	if (envp == NULL || envp[0] == NULL)
		return (0);
	while (envp[x] != NULL)
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
	return (x);
}

void		envp_null(char *data)
{
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *) * 2)) == NULL)
		return ;
	new_envp[0] = ft_strdup(data);
	return ;
}

void		envp_no_null(char *data)
{
	int		x;
	char	*p;
	char	*tmp_data;

	if ((tmp_data = ft_strdup(data)) == NULL)
		return ;
	p = ft_strchr(tmp_data, '=');
	*p = '\0';
	x = find_var(tmp_data);
	if (envp[x] == NULL)
	{
		remalloc_envp(x, x + 1);
		envp[x] = ft_strdup(data);
	}
	else
	{
		free(envp[x]);
		envp[x] = ft_strdup(data);
	}
	free(tmp_data);
	return ;
}

void		add_envp(char *data)
{
	if (envp == NULL || envp[0] == NULL)
	{
		envp_null(data);
		return ;
	}
	else
		envp_no_null(data);
	return ;
}
