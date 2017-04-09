/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:23:56 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/07 12:34:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*creat_new(char *envp)
{
	char	*p;
	char	*tmp_envp;
	t_env	*new;

	tmp_envp = ft_strdup(envp);
	new = ft_memalloc(sizeof(t_env));
	p = ft_strchr(tmp_envp, '=');
	new->data = ft_strdup(p + 1);
	*p = '\0';
	new->name = ft_strdup(tmp_envp);
	new->next = NULL;
	free(tmp_envp);
	return (new);
}

t_env		*creat_t_env(char **envp)
{
	int		x;
	t_env	*new;
	t_env	*tmp;
	t_env	*begin_env;

	x = 1;
	if (envp[0] == NULL)
		return (NULL);
	begin_env = creat_new(envp[0]);
	tmp = begin_env;
	while (envp[x] != NULL)
	{
		new = creat_new(envp[x]);
		tmp->next = new;
		tmp = tmp->next;
		x++;
	}
	return (begin_env);
}

static int	ft_len_list(t_env *env)
{
	int		x;
	t_env	*tmp;

	x = 0;
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		x++;
	}
	return (x);
}

char		**creat_char_envp(t_env *env)
{
	int		x;
	int		len_list;
	char	**envp;
	t_env	*tmp;

	x = 0;
	if (env == NULL)
		return (NULL);
	tmp = env;
	len_list = ft_len_list(env);
	if ((envp = ft_memalloc(sizeof(char *) * len_list + 1)) == NULL)
		return (0);
	while (x < len_list)
	{
		if ((envp[x] = ft_memalloc(sizeof(char *) * (ft_strlen(tmp->name) +
							ft_strlen(tmp->data) + 2))) == NULL)
			return (0);
		ft_sprintf(envp[x], "%s=%s", tmp->name, tmp->data);
		tmp = tmp->next;
		x++;
	}
	return (envp);
}
