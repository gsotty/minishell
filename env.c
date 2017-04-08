/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 10:44:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/04 18:09:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verif_flag_env(char **cmd, int x, t_flag_env *flag)
{
	int		y;

	y = 1;
	if (cmd[x][0] == '-' && cmd[x][1] != '\0')
	{
		while (cmd[x][y] != '\0')
		{
			if (cmd[x][y] == 'i')
				flag->i_min = 1;
			else if (cmd[x][y] == 'u')
			{
				flag->u_min += 1;
				if (cmd[x][y + 1] != '\0')
				{
					flag->name = ft_strdup(cmd[x] + y + 1);
					return (1);
				}
				else if (cmd[x][y + 1] == '\0' && cmd[x + 1] != NULL)
				{
					flag->name = ft_strdup(cmd[x + 1]);
					return (2);
				}
				else
				{
					ft_printf("env: option requires an argument -- %c\nusage:",
							cmd[x][y]);
					ft_printf(" env [-i] [-u name] [name=value ...]");
					ft_printf("\n\t   [utility [argument ...]]\n");
					return (-1);
				}
			}
			else
			{
				ft_printf("env: illegal option -- %c\nusage: env [-i] ",
						cmd[x][y]);
				ft_printf("[-u name] [name=value ...]\n\t   [utility [argume");
				ft_printf("nt ...]]\n");
				return (-1);
			}
			y++;
		}
		return (1);
	}
	else if (cmd[x][0] == '-' && cmd[x][1] == '\0')
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
		if ((ret = verif_flag_env(cmd, x,flag)) == 0)
			break ;
		if (ret == -1)
			return (-1);
		if (ret == 2)
			x++;
		x++;
	}
	return (x);
}

int		ft_env(char **cmd, t_env *env)
{
	int			y;
	pid_t		father;
	int			ret;
	int			x;
	char		**envp;
	t_env		*tmp;
	t_flag_env	flag;

	x = 0;
	y = 0;
	envp = creat_char_envp(env);
	ft_memset(&flag, 0, sizeof(t_flag_env));
	if ((ret = check_flag_env(cmd, &flag)) == -1)
		return (1);
	envp = creat_char_envp(env);
	if (cmd[ret] == NULL && flag.u_min == 0)
	{
		if (flag.i_min == 1)
		{
		}
		else
		{
			tmp = env;
			while (tmp != NULL)
			{
				ft_printf("%s\n", envp[x]);
				tmp = tmp->next;
				x++;
			}
		}
	}
	else
	{
		if (flag.i_min == 1)
			env = NULL;
		if (flag.u_min == 1)
		{
			env = remove_env(env, flag.name);
		}
		while (cmd[ret + y] != NULL)
		{
			if (ft_strchr(cmd[ret + y], '=') != NULL)
			{
				env = add_env(env, cmd[ret + y]);
				envp = creat_char_envp(env);
			}
			else
				break ;
			y++;
		}
		while (cmd[ret + y] != NULL)
		{
			if (ft_strcmp(cmd[ret + y], "env") == 0)
			{
				father = fork();
				if (father > 0)
					wait(NULL);
				if (father == 0)
				{
					ft_env(cmd + ret + y, env);
					exit(0);
				}
			}
			else
				exe_cmd(cmd + ret + y, env);
			return (0);
			y++;
		}
		if (cmd[ret + y] == NULL)
		{
			cmd[0] = ft_strdup("env");
			cmd[1] = NULL;
			ft_env(cmd, env);
		}
	}
	return (0);
}
