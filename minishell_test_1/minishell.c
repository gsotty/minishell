/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:31:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/12 20:10:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

void		print_prompt(void)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	if (pwd[0] == '/' && pwd[1] == '\0')
		ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
				ft_strrchr(pwd, '/'));
	else
		ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
				ft_strrchr(pwd, '/') + 1);
}

static char	*creat_buf(char *buf)
{
	int		x;
	int		ret;
	int		cont;
	char	c;

	x = 0;
	cont = 0;
	ft_memset(buf, '\0', MAX_CANON);
	while (((ret = read(0, &c, 1)) && c != '\n') && cont < MAX_CANON - 1)
	{
		buf[cont] = c;
		cont++;
	}
	if (ret == 0)
		exit(0);
	buf[cont] = '\0';
	while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
		x++;
	if (buf[x] == '\0')
		return (NULL);
	return (buf);
}

static char	**while_minishell(char **envp, int x)
{
	char	buf[MAX_CANON];

	print_prompt();
	signal(SIGINT, traite_signal);
	if (creat_buf(buf) != NULL)
	{
		signal(SIGINT, traite_signal_fork);
		while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
			x++;
		if (ft_strstr(buf, "exit") != NULL)
		{
			x += 4;
			while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
				x++;
			if (buf[x] == '\0')
			{
				free_tab(envp);
				exit(0);
			}
		}
		if (buf[0] != '\0')
			envp = exe(buf, envp);
	}
	return (envp);
}

static int	minishell(char **envp_begin)
{
	char	**envp;

	envp = creat_envp(envp_begin);
	while (1)
		envp = while_minishell(envp, 0);
	free_tab(envp);
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	if (argc == 0)
		return (1);
	if (!argv)
		return (1);
	return (minishell(envp));
}
