/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:31:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/22 15:50:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

void		print_prompt(void)
{
	char	*tmp;
	char	pwd[PATH_MAX];

	tmp = NULL;
	if (access(tmp = find_var_env("PWD"), F_OK) == 0)
	{
		if (tmp[0] == '/' && tmp[1] == '\0')
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(tmp, '/'));
		else
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(tmp, '/') + 1);
	}
	else
	{
		getcwd(pwd, PATH_MAX);
		if (pwd[0] == '/' && pwd[1] == '\0')
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/'));
		else
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/') + 1);
	}
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
	while (((ret = read(0, &c, 1)) && c != '\n'))
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

static void	while_minishell(int x)
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
			exe(buf);
	}
	return ;
}

int			minishell(char **envp_begin)
{
	envp = creat_envp(envp_begin);
	while (1)
		while_minishell(0);
	free_tab(envp);
	return (0);
}
