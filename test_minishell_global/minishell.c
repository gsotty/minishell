/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:31:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 17:09:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

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
				free_tab(g_envp);
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
	g_envp = creat_env(envp_begin);
	while (1)
		while_minishell(0);
	free_tab(g_envp);
	return (0);
}
