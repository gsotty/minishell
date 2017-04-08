/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:31:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/08 16:33:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

static void	print_prompt(void)
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
	while (((ret = read(0, &c, 1)) && c != '\n') && cont < MAX_CANON)
	{
		buf[cont] = c;
		cont++;
	}
	buf[cont] = '\0';
	while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
		x++;
	if (buf[x] == '\0')
		return (NULL);
	return (buf);
}

static int	minishell(char **envp)
{
	int		x;
	char	buf[MAX_CANON];

	while (1)
	{
		print_prompt();
		if (creat_buf(buf) != NULL)
		{
			x = 0;
			while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
				x++;
			if (ft_strstr(buf, "exit") != NULL)
			{
				x += 4;
				while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
					x++;
				if (buf[x] == '\0')
					return (0);
			}
			if (buf[0] != '\0')
				envp = exe(buf, envp);
		}
	}
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
