/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:10:43 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/07 14:14:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_var_env(t_env *env, char *name)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		if (ft_strcmp(tmp_env->name, name) == 0)
			break ;
		tmp_env = tmp_env->next;
	}
	return (tmp_env);
}
