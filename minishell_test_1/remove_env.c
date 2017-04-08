/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/08 13:38:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_env(t_env *begin_env, char *name)
{
	t_env	*env;
	t_env	*tmp_env;

	tmp_env = NULL;
	if (begin_env == NULL || name == NULL)
		return (begin_env);
	else
	{
		env = begin_env;
		if (ft_strcmp(name, begin_env->name) == 0)
		{
			free(begin_env->name);
			free(begin_env->data);
			tmp_env = begin_env;
			begin_env = begin_env->next;
			free(tmp_env);
			return (begin_env);
		}
		while (env->next != NULL)
		{
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
