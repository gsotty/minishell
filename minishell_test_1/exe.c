/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:34:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 17:34:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_fork(char **argv, char **envp)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		return (envp);
	}
	if (father == 0)
	{
		envp = ft_env(argv, envp);
		free_tab(envp);
		exit(0);
	}
	return (envp);
}

char		**exe_cmd(int argc, char **argv, char **envp)
{
	if (ft_strcmp(argv[0], "env") == 0)
		envp = env_fork(argv, envp);
	else if (ft_strcmp(argv[0], "echo") == 0)
		echo(argv);
	else if (ft_strcmp(argv[0], "setenv") == 0)
		envp = ft_setenv(envp, argv);
	else if (ft_strcmp(argv[0], "unsetenv") == 0)
		envp = ft_unsetenv(envp, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		envp = cd(argv, envp);
	else
		envp = exe_fork(argc, argv, envp);
	return (envp);
}

static int	len_tab(char **argv)
{
	int		x;

	x = 0;
	while (argv[x] != NULL)
		x++;
	return (x);
}

char		**exe(char *buf, char **envp)
{
	int		argc;
	char	**argv;

	argv = ft_strsplit_space(buf, " \t");
	argc = len_tab(argv);
	envp = exe_cmd(argc, argv, envp);
	free_tab(argv);
	return (envp);
}
