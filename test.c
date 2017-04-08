/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:16:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/05 15:15:51 by gsotty           ###   ########.fr       */
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

/*
   int			exe_cmd(char **cmd, t_env *env)
   {
   int		y;
   int		x;
   int		ret;
   int		len_cmd;
   pid_t	father;
   char	*tmp_cmd;
   char	*tmp_join;
   char	**path;
   char	**envp;

   x = 0;
   y = 0;
   ret = 0;
   envp = creat_char_envp(env);
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
   if (envp == NULL)
   {
   ft_printf("minishell: %s: No such file or directory\n",
   cmd[0]);
   return (0);
   }
   while ((ft_strstr(envp[x], "PATH=") == NULL) && envp[x] != NULL)
   x++;
   if (envp[x] != NULL)
   {
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
   ret = access(tmp_join = ft_strjoin(path[y], cmd[0]), F_OK
   | X_OK);
   if (ret == 0 && access(tmp_join, F_OK | X_OK) == 0)
   {
   father = fork();
   if (father > 0)
   {
   wait(NULL);
   return (1);
   }
   if (father == 0)
   {
   execve(tmp_join, cmd, envp);
   ft_printf("minishell: command not found: %s\n",
   cmd[0] + 1);
   exit(0);
   }
   }
   free(tmp_join);
y++;
}
}
ft_printf("minishell: command not found: %s\n", cmd[0] + 1);
}
return (0);
}
*/

int			len_argc(char **cmd)
{
	int		x;

	x = 0;
	while (cmd[x] != NULL)
		x++;
	return (x);
}

int			exe(char **cmd, t_env *begin_env)
{

	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd, begin_env);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(begin_env, cmd);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ft_unsetenv(begin_env, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd(begin_env, cmd);
	else
		exe_cmd(cmd, begin_env);
	return (0);
}

int			minishell(int argc, char **argv, char **envp)
{
	int		y;
	int		ret;
	int		len_cmd;
	char	buf[3746];
	char	**cmd;
	t_env	*begin_env;
	char	*pwd;

	y = 0;
	if (argc == 0)
		return (0);
	if (argv)
	{
	}
	ret = 0;
	if ((pwd = ft_memalloc(3764)) == NULL)
		return (0);
	getcwd(pwd, 3764);
	ft_printf("\033[32m%s\033[0m\t\033[36m$>\033[0m ",
			ft_strrchr(pwd, '/') + 1);
	begin_env = creat_t_env(envp);
	while (read(0, buf, 1))
	{
		y = 0;
		if (buf[0] != '\0')
		{
			if (ft_strcmp(buf, "exit") == 0)
				return (0);
			cmd = ft_strsplit_space(buf);
			len_cmd = len_argc(cmd);
			exe(cmd, begin_env);
			y = 0;
			while (cmd[y] == NULL)
			{
				free(cmd[y]);
				y++;
			}
			free(cmd);
		}
		free(pwd);
		if ((pwd = ft_memalloc(3764)) == NULL)
			return (0);
		getcwd(pwd, 3764);
		ft_printf("\033[32m%s\033[0m\t\033[36m$>\033[0m ",
				ft_strrchr(pwd, '/') + 1);
	}
	y = 0;
	while (envp[y] == NULL)
	{
		free(envp[y]);
		y++;
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	return (minishell(argc, argv, envp));
}
