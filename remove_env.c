/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 16:47:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_env(t_env *begin_env, char *name)
{
	t_env	*env;
	t_env	*tmp_env;

	if (begin_env == NULL || name == NULL)
		return (begin_env);
	else
	{
		env = begin_env;
		ft_printf("%s, %s\n", name, env->name);
		if (ft_strcmp(name, env->name) == 0)
		{
			begin_env = env->next;
			free(env);
			return (begin_env);
		}
		while (env->next != NULL)
		{
			ft_printf("%s, %s\n", name, env->next->name);
			if (ft_strcmp(name, env->next->name) == 0)
			{
				tmp_env = env->next;
				env->next = env->next->next;
				free(tmp_env);
				return (begin_env);
			}
			env = env->next;
		}
		return (begin_env);
	}
}
