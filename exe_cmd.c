/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 09:44:23 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/06 12:51:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		inst_exe_cmd(char **cmd, t_env *env)
{
	int		x;
	char	**envp;
	pid_t	father;

	x = 0;
	envp = creat_char_envp(env);
	father = fork();
	if (father > 0)
	{
		wait(NULL);
		while (envp[x] != NULL)
		{
			free(envp[x]);
			x++;
		}
		free(envp);
		return (0);
	}
	if (father == 0)
		execve(cmd[0], cmd, envp);
	while (envp[x] != NULL)
	{
		free(envp[x]);
		x++;
	}
	free(envp);
	return (0);
}

int		noinst_exe_cmd(char **cmd, t_env *env)
{
	int		j;
	int		x;
	int		y;
	t_env	*tmp;
	char	*tmp_join;
	char	*tmp_cmd;
	char	**path;

	j = 0;
	x = 0;
	y = 0;
	tmp = env;
	if (env == NULL)
	{
		ft_printf("minishell: %s: no such file or directory\n", cmd[0]);
		return (1);
	}
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->name, "PATH") != NULL)
			break ;
		tmp = tmp->next;
	}
	path = ft_strsplit(tmp->data, ':');
	tmp_cmd = ft_strjoin("/", cmd[0]);
	while (path[y] != NULL)
	{
		if ((access(tmp_join = ft_strjoin(path[y], tmp_cmd), F_OK | X_OK)) == 0)
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(tmp_join);
			inst_exe_cmd(cmd, env);
			free(tmp_join);
			free(tmp_cmd);
			while (path[j] != NULL)
			{
				free(path[j]);
				j++;
			}
			free(path);
			return (0);
		}
		free(tmp_join);
		y++;
	}
	while (path[j] != NULL)
	{
		free(path[j]);
		j++;
	}
	free(path);
	ft_printf("minishell: commande not found: %s\n", cmd[0] + 1);
	return (1);
}

int		exe_cmd(char **cmd, t_env *env)
{
	if (access(cmd[0], F_OK | X_OK) == 0)
		inst_exe_cmd(cmd, env);
	else
		noinst_exe_cmd(cmd, env);
	return (0);
}
