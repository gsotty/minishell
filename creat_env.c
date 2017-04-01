/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:23:56 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/01 12:47:07 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*creat_new(char *envp)
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
	return (new);
}

t_env	*creat_t_env(char **envp)
{
	int		x;
	t_env	*new;
	t_env	*tmp;
	t_env	*begin_env;

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

int		ft_len_list(t_env *env)
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

char	**creat_char_envp(t_env *env)
{
	int		x;
	int		len_list;
	char	**envp;
	t_env	*tmp;

	x = 0;
	tmp = env;
	len_list = ft_len_list(env);
	if ((envp = ft_memalloc(sizeof(char *) * len_list)) == NULL)
		return (0);
	while (tmp != NULL)
	{
		if ((envp[x] = ft_memalloc(sizeof(char *) * (ft_strlen(tmp->name) +
							ft_strlen(tmp->data + 2)))) == NULL)
			return (0);
		ft_sprintf(envp[x], "%s=%s\n", tmp->name, tmp->data);
		tmp = tmp->next;
		x++;
	}
	return (envp);
}
