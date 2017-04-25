/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:34:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 13:10:37 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_fork(char **argv)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		return ;
	}
	if (father == 0)
	{
		ft_env(argv);
		free_tab(g_envp);
		exit(0);
	}
	return ;
}

void		exe_cmd(int argc, char **argv)
{
	if (ft_strcmp(argv[0], "env") == 0)
		env_fork(argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		echo(argv);
	else if (ft_strcmp(argv[0], "setenv") == 0)
		ft_setenv(argv);
	else if (ft_strcmp(argv[0], "unsetenv") == 0)
		ft_unsetenv(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		cd(argv);
	else
		exe_fork(argc, argv);
	return ;
}

static int	len_tab(char **argv)
{
	int		x;

	x = 0;
	while (argv[x] != NULL)
		x++;
	return (x);
}

void		exe(char *buf)
{
	int		argc;
	char	**argv;

	argv = ft_strsplit_space(buf, " \t");
	argc = len_tab(argv);
	exe_cmd(argc, argv);
	free_tab(argv);
	return ;
}
