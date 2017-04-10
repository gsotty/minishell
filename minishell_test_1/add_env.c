/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:34:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 17:21:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_var(char **envp, char *tmp_data)
{
	int		x;
	char	*p;
	char	*tmp_envp;

	x = 0;
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

char		**envp_null(char *data)
{
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *))) == NULL)
		return (NULL);
	new_envp[0] = ft_strdup(data);
	return (new_envp);
}

char		**envp_no_null(char **envp, char *data)
{
	int		x;
	char	*p;
	char	*tmp_data;

	x = 0;
	tmp_data = ft_strdup(data);
	p = ft_strchr(tmp_data, '=');
	*p = '\0';
	x = find_var(envp, tmp_data);
	if (envp[x] == NULL)
	{
		envp = remalloc_envp(envp, x, x + 1);
		envp[x] = ft_strdup(data);
	}
	else
	{
		free(envp[x]);
		envp[x] = ft_strdup(data);
	}
	free(tmp_data);
	return (envp);
}

char		**add_env(char **envp, char *data)
{
	if (envp == NULL || envp[0] == NULL)
	{
		if ((envp = envp_null(data)) == NULL)
			return (NULL);
		return (envp);
	}
	else
		envp = envp_no_null(envp, data);
	return (envp);
}
