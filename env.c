/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 10:44:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/01 12:49:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verif_flag_env(char *cmd, t_flag_env *flag)
{
	int		y;

	y = 1;
	if (cmd[0] == '-' && cmd[1] != '\0')
	{
		while (cmd[y] != '\0')
		{
			if (cmd[y] == 'i')
				flag->i_min = 1;
			else if (cmd[y] == 'P')
				flag->p_maj = 1;
			else if (cmd[y] == 'S')
				flag->s_maj = 1;
			else if (cmd[y] == 'u')
				flag->u_min = 1;
			else if (cmd[y] == 'v')
				flag->v_min = 1;
			else
			{
				ft_printf("env: illegal option -- %c\nusage: env [-i", cmd[y]);
				ft_printf("v] [-P utilpath] [-S string] [-u name]\n\t   [nam");
				ft_printf("e=value ...] [utility [argument ...]]\n");
				return (-1);
			}
			y++;
		}
		return (1);
	}
	else if (cmd[0] == '-' && cmd[1] == '\0')
		flag->i_min = 1;
	else
		return (0);
	return (1);
}

int		check_flag_env(char **cmd, t_flag_env *flag)
{
	int		x;
	int		ret;

	x = 1;
	while (cmd[x] != NULL)
	{
		if ((ret = verif_flag_env(cmd[x], flag)) == 0)
			break ;
		if (ret == -1)
			return (-1);
		x++;
	}
	return (x);
}

int		env(char **cmd, t_env *env)
{
	int			x;
	char		**envp;
	t_env		*tmp;
	t_flag_env	flag;

	x = 0;
	if (check_flag_env(cmd, &flag) == -1)
		return (1);
	envp = creat_char_envp(env);
	tmp = env;
	while (tmp != NULL)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->data);
		ft_printf("%s", envp[x]);
		tmp = tmp->next;
		x++;
	}
	return (0);
}
