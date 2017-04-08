/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:34:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 15:00:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_env(t_env *begin_env, char *envp)
{
	t_env	*env;
	t_env	*new;
	char	*tmp;
	char	*p;

	if (begin_env == NULL)
	{
		new = creat_new(envp);
		begin_env = new;
		return (begin_env);
	}
	else
	{
		env = begin_env;
		while (env != NULL)
		{
			tmp = ft_strdup(envp);
			p = ft_strchr(tmp, '=');
			*p = '\0';
			if (env->next == NULL && ft_strcmp(env->name, tmp) != 0)
			{
				new = creat_new(envp);
				env->next = new;
				return (begin_env);
			}
			else
			{
				if (ft_strcmp(env->name, tmp) == 0)
				{
					free(env->data);
					p = ft_strchr(envp, '=');
					env->data = ft_strdup(p + 1);
					return (begin_env);
				}
				env = env->next;
				free(tmp);
			}
		}
		return (begin_env);
	}
}
