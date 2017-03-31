/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:16:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			exe_cmd(char **cmd, char **envp)
{
	int		y;
	int		x;
	int		ret;
	int		len_cmd;
	pid_t	father;
	char	*tmp_cmd;
	char	*tmp_join;
	char	**path;

	x = 0;
	y = 0;
	ret = 0;
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return (1);
		}
		if (father == 0)
			execve(cmd[0], cmd, envp);
	}
	else
	{
		while ((ft_strstr(envp[x], "PATH=") == NULL) && envp[x] != NULL)
			x++;
		path = ft_strsplit(envp[x] + 5, ':');
		len_cmd = ft_strlen(cmd[0]);
		if ((tmp_cmd = ft_memalloc(len_cmd + 2)) == NULL)
			return (-1);
		ft_memcpy(tmp_cmd, "/", 1);
		ft_memcpy(tmp_cmd + 1, cmd[0], len_cmd);
		tmp_cmd[len_cmd + 1] = '\0';
		free(cmd[0]);
		cmd[0] = ft_strdup(tmp_cmd);
		free(tmp_cmd);
		while (path[y] != NULL)
		{
			ret = access(tmp_join = ft_strjoin(path[y], cmd[0]), F_OK | X_OK);
			if (ret == 0)
			{
				father = fork();
				if (father > 0)
				{
					wait(NULL);
					return (1);
				}
				if (father == 0)
					execve(tmp_join, cmd, envp);
			}
			free(tmp_join);
			y++;
		}
		ft_printf("minishell: command not found: %s\n", cmd[0] + 1);
	}
	return (0);
}

int			len_argc(char **cmd)
{
	int		x;

	while (cmd[x] != NULL)
		x++;
	return (x);
}

int			minishell(int argc, char **argv, char **envp)
{
	int		y=0;
	int		j=0;
	int		x;
	int		ret;
	int		len_cmd;
	char	*buf;
	char	**cmd;


	ret = 0;
	ft_putstr("$> ");
	while (((ret = get_next_line(0, &buf)) > 0))
	{
		y = 0;
		if (buf[0] != '\0')
		{
			if (ft_strcmp(buf, "exit") == 0)
				return (0);
			cmd = ft_strsplit_space(buf);
			len_cmd = len_argc(cmd);
			if (ft_strcmp(cmd[0], "env") == 0)
			{
				while (envp[y] != NULL)
				{
					ft_printf("%s\n", envp[y]);
					y++;
				}
			}
			else if (ft_strcmp(cmd[0], "echo") == 0)
				echo(cmd);
			else if (ft_strcmp(cmd[0], "cd") == 0)
			{
				cd(cmd);
			}
			else
			{
				exe_cmd(cmd, envp);
			}
		}
		ft_putstr("$> ");
		x++;
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	return (minishell(argc, argv, envp));
}
